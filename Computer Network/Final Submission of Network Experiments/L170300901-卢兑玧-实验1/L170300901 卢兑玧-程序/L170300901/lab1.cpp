#include <stdio.h> 
#include <Windows.h> 
#include <process.h> 
#include <string.h> 
#include <tchar.h>

#pragma comment(lib,"Ws2_32.lib") 

#define MAXSIZE 65507 
#define HTTP_PORT 80

#define CACHE_MAXSIZE 100 
#define DATELENGTH 40
#define DATELENGTH 40

struct HttpHeader {
	char method[4];
	char url[1024];  //   url 
	char host[1024];
	char cookie[1024 * 10]; //cookie 
	HttpHeader() {
		ZeroMemory(this, sizeof(HttpHeader));
	}
};

struct cache_HttpHeader {
	char method[4]; 
	char url[1024];  //   url 
	char host[1024];
	cache_HttpHeader() {
		ZeroMemory(this, sizeof(cache_HttpHeader));
	}
};
struct __CACHE {
	cache_HttpHeader htphed;
	char buffer[MAXSIZE];
	char date[DATELENGTH];
	__CACHE() {
		ZeroMemory(this->buffer, MAXSIZE);
		ZeroMemory(this->buffer, sizeof(date));
	}

};
int __CACHE_number = 0;//
__CACHE cache[CACHE_MAXSIZE];//

BOOL InitSocket();
BOOL ParseHttpHead(char* buffer, HttpHeader* httpHeader);
BOOL ConnectToServer(SOCKET* serverSocket, char* host);
unsigned int __stdcall ProxyThread(LPVOID lpParameter);
int Cache_find(__CACHE* cache, HttpHeader htp);


SOCKET ProxyServer;
sockaddr_in ProxyServerAddr;
const int ProxyPort = 10240;

const char* host[10] = { "today.hit.edu.cn", "jwts.hit.edu.cn", "www.hit.edu.cn" };
const int host_number = 3;


const char* host_to_another = "cwc.hit.edu.cn";//cs.hit.edu.cn
const char* another[2] = { "cs.hit.edu.cn","http://cwc.hit.edu.cn" };//

struct ProxyParam {
	SOCKET clientSocket;
	SOCKET serverSocket;
};

int _tmain(int argc, _TCHAR* argv[])
{

	printf("the proxy server is starting \n");
	printf("initialize \n");
	if (!InitSocket()) {

		printf("socket initialize fail \n");
		return -1;
	}
	printf("The proxy server is running, monitoring port  %d\n", ProxyPort);
	SOCKET acceptSocket = INVALID_SOCKET;
	ProxyParam* lpProxyParam;
	HANDLE hThread;
	DWORD dwThreadID;

	sockaddr_in verAddr;
	int hahaha = sizeof(SOCKADDR);
	while (true) {
		acceptSocket = accept(ProxyServer, (SOCKADDR*)&verAddr, &(hahaha));
		lpProxyParam = new ProxyParam;
		if (lpProxyParam == NULL) {
			continue;
		}
		if (strcmp("127.0.0.1", inet_ntoa(verAddr.sin_addr))) {
			printf("Restricted user access！\n");
			continue;
		}
		lpProxyParam->clientSocket = acceptSocket;
		hThread = (HANDLE)_beginthreadex(NULL, 0,
			&ProxyThread, (LPVOID)lpProxyParam, 0, 0);
		CloseHandle(hThread);
		Sleep(200);
	}
	closesocket(ProxyServer);
	WSACleanup();
	return 0;
}

BOOL InitSocket() {

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);  
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		printf("Load Winsock Failure, Error code: %d\n", WSAGetLastError());
		return FALSE;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		printf("Can 't find the right WInsock version\n");
		WSACleanup();
		return FALSE;
	}
	ProxyServer = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == ProxyServer) {
		printf("Create a socket failure, error code：%d\n", WSAGetLastError());
		return FALSE;
	}
	ProxyServerAddr.sin_family = AF_INET;
	ProxyServerAddr.sin_port = htons(ProxyPort);
	ProxyServerAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(ProxyServer, (SOCKADDR*)&ProxyServerAddr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		printf("Binding socket failure\n");
		return FALSE;
	}
	if (listen(ProxyServer, SOMAXCONN) == SOCKET_ERROR) {
		printf("Monitoring port:%d failure", ProxyPort);
		return FALSE;
	}
	return TRUE;
}

unsigned int __stdcall ProxyThread(LPVOID lpParameter) {
	char Buffer[MAXSIZE];
	char* CacheBuffer;
	ZeroMemory(Buffer, MAXSIZE);
	SOCKADDR_IN clientAddr;
	int length = sizeof(SOCKADDR_IN);
	int recvSize;
	int ret;
	HttpHeader* httpHeader;
	bool change;
	int j;
	int find;
	char* chacheBuff;
	const char* delim;
	char* p;
	bool cun;

	recvSize = recv(((ProxyParam
		*)lpParameter)->clientSocket, Buffer, MAXSIZE, 0);
	if (recvSize <= 0) {
		goto error;
	}

	httpHeader = new HttpHeader();
	CacheBuffer = new char[recvSize + 1];
	ZeroMemory(CacheBuffer, recvSize + 1);
	memcpy(CacheBuffer, Buffer, recvSize);
	change = ParseHttpHead(CacheBuffer, httpHeader);
	delete CacheBuffer;

	j = 0;

	for (j = 0; j < host_number; j++)
	{
		int i = 0;
		bool find = true;
		for (i = 0; i < strlen(host[j]); i++) {
			if (host[j][i] != httpHeader->host[i]) {
				find = false;
				break;
			}
		}
		if (find)
			goto error;
	}


	if (!ConnectToServer(&((ProxyParam
		*)lpParameter)->serverSocket, httpHeader->host)) {
		goto error;
	}
	printf("proxy ConnectIons Host %s Successful\n", httpHeader->host);

	if (change) {
		char* CacheBuffer;
		CacheBuffer = new char[MAXSIZE];
		ZeroMemory(CacheBuffer, MAXSIZE);
		//memcpy(CacheBuffer, Buffer, recvSize);
		int ii = 0, lengthth = 0;
		for (ii = 0; ii < strlen(httpHeader->method); ii++) {
			CacheBuffer[lengthth++] = httpHeader->method[ii];
		}
		CacheBuffer[lengthth++] = ' ';
		for (ii = 0; ii < strlen(another[1]); ii++) {
			CacheBuffer[lengthth++] = another[1][ii];
		}
		CacheBuffer[lengthth++] = ' ';
		const char* hh = "HTTP/1.1";
		for (ii = 0; ii < strlen(hh); ii++) {
			CacheBuffer[lengthth++] = hh[ii];
		}
		CacheBuffer[lengthth++] = '\r';
		CacheBuffer[lengthth++] = '\n';
		const char* hhh = "HOST: ";
		for (ii = 0; ii < strlen(hhh); ii++) {
			CacheBuffer[lengthth++] = hhh[ii];
		}
		for (ii = 0; ii < strlen(httpHeader->host); ii++) {
			CacheBuffer[lengthth++] = httpHeader->host[ii];
		}
		CacheBuffer[lengthth++] = '\r';
		CacheBuffer[lengthth++] = '\n';
		char* ptr;
		const char* delim = "\r\n";
		char* p = strtok_s(Buffer, delim, &ptr);
		int length1 = strlen(p);
		length1 += 2;
		p = strtok_s(NULL, delim, &ptr);
		length1 += strlen(p);
		length1 += 2;
		for (ii = 1; ii < recvSize - length1 + 1; ii++) {
			CacheBuffer[lengthth++] = ptr[ii];
		}
		memcpy(Buffer, CacheBuffer, max(strlen(CacheBuffer), recvSize));
		delete CacheBuffer;
	}

	find = Cache_find(cache, *httpHeader);
	if (find >= 0) {
		char* CacheBuffer;
		char Buffer2[MAXSIZE];
		int i = 0, length = 0, length2 = 0;
		ZeroMemory(Buffer2, MAXSIZE);
		CacheBuffer = new char[recvSize + 1];
		ZeroMemory(CacheBuffer, recvSize + 1);
		memcpy(CacheBuffer, Buffer, recvSize);

		const char* delim = "\r\n";
		char* ptr;
		char* p = strtok_s(CacheBuffer, delim, &ptr);
		length += strlen(p);
		length += 2;
		p = strtok_s(NULL, delim, &ptr);
		length += strlen(p);
		length += 2;
		length2 = length;

		const char* ife = "If-Modified-Since: ";
		for (i = 0; i < length; i++) {
			Buffer2[i] = Buffer[i];
		}
		for (i = 0; i < strlen(ife); i++)
		{
			Buffer2[length + i] = ife[i];
		}
		length = length + strlen(ife);
		for (i = 0; i < strlen(cache[find].date); i++)
		{
			Buffer2[length + i] = cache[find].date[i];
		}
		length += strlen(cache[find].date);
		Buffer2[length++] = '\r';
		Buffer2[length++] = '\n';
		for (i = length2; i < recvSize; i++) {
			Buffer2[length++] = Buffer[i];
		}
		delete CacheBuffer;


		ret = send(((ProxyParam*)lpParameter)->serverSocket, Buffer2, strlen(Buffer2)
			+ 1, 0);
		recvSize = recv(((ProxyParam
			*)lpParameter)->serverSocket, Buffer2, MAXSIZE, 0);

		if (recvSize <= 0) {
			goto error;
		}

		const char* blank = " ";
		const char* Modd = "304";
		if (!memcmp(&Buffer2[9], Modd, strlen(Modd)))
		{
			ret = send(((ProxyParam
				*)lpParameter)->clientSocket, cache[find].buffer, strlen(cache[find].buffer) + 1, 0);
			goto error;
		}
	} 
	ret = send(((ProxyParam*)lpParameter)->serverSocket, Buffer, strlen(Buffer)
		+ 1, 0);
	recvSize = recv(((ProxyParam
		*)lpParameter)->serverSocket, Buffer, MAXSIZE, 0);
	if (recvSize <= 0) {
		goto error;
	}

	chacheBuff = new char[MAXSIZE];
	ZeroMemory(chacheBuff, MAXSIZE);
	memcpy(chacheBuff, Buffer, MAXSIZE);
	delim = "\r\n";
	char* ptr;
	char dada[DATELENGTH];
	ZeroMemory(dada, sizeof(dada));
	p = strtok_s(chacheBuff, delim, &ptr);
	cun = false;
	while (p) {
		if (p[0] == 'L') {
			if (strlen(p) > 15) {
				char header[15];
				ZeroMemory(header, sizeof(header));
				memcpy(header, p, 14);
				if (!(strcmp(header, "Last-Modified:")))
				{
					memcpy(dada, &p[15], strlen(p) - 15);
					cun = true;
					break;
				}
			}
		}
		p = strtok_s(NULL, delim, &ptr);
	}
	if (cun) {
		if (find >= 0)
		{
			memcpy(&(cache[find].buffer), Buffer, strlen(Buffer));
			memcpy(&(cache[find].date), dada, strlen(dada));
		}
		else
		{
			memcpy(&(cache[__CACHE_number % CACHE_MAXSIZE].htphed.host), httpHeader->host, strlen(httpHeader->host));
			memcpy(&(cache[__CACHE_number % CACHE_MAXSIZE].htphed.method), httpHeader->method, strlen(httpHeader->method));
			memcpy(&(cache[__CACHE_number % CACHE_MAXSIZE].htphed.url), httpHeader->url, strlen(httpHeader->url));
			memcpy(&(cache[__CACHE_number % CACHE_MAXSIZE].buffer), Buffer, strlen(Buffer));
			memcpy(&(cache[__CACHE_number % CACHE_MAXSIZE].date), dada, strlen(dada));
			__CACHE_number++;
		}
	}

	ret = send(((ProxyParam
		*)lpParameter)->clientSocket, Buffer, sizeof(Buffer), 0);
error:
	printf("Disable socket agent connection to host \n");
	Sleep(200);
	closesocket(((ProxyParam*)lpParameter)->clientSocket);
	closesocket(((ProxyParam*)lpParameter)->serverSocket);
	delete    lpParameter;
	_endthreadex(0);
	return 0;
}

BOOL ParseHttpHead(char* buffer, HttpHeader* httpHeader) {
	char* p;
	char* ptr;
	bool change = false;
	const char* delim = "\r\n";
	/*

	*/
	p = strtok_s(buffer, delim, &ptr);
	printf("%s\n", p);
	if (p[0] == 'G') {
		memcpy(httpHeader->method, "GET", 3);

		memcpy(httpHeader->url, &p[4], strlen(p) - 13);
	}
	else if (p[0] == 'P') {
		memcpy(httpHeader->method, "POST", 4);
		memcpy(httpHeader->url, &p[5], strlen(p) - 14);
	}
	printf("%s\n", httpHeader->url);
	p = strtok_s(NULL, delim, &ptr);

	while (p) {
		switch (p[0]) {
		case 'H':
			if (!memcmp(&p[6], host_to_another, strlen(p) - 6))
			{
				memcpy(httpHeader->host, another[0], strlen(another[0]));
				memcpy(httpHeader->url, another[1], strlen(another[1]));
				change = true;
			}
			else {
				memcpy(httpHeader->host, &p[6], strlen(p) - 6);
			}
			break;
		case 'C'://Cookie 
			if (strlen(p) > 8) {
				char header[8];
				ZeroMemory(header, sizeof(header));
				memcpy(header, p, 6);
				if (!strcmp(header, "Cookie")) {
					memcpy(httpHeader->cookie, &p[8], strlen(p) - 8);
				}
			}
			break;
		default:
			break;
		}
		p = strtok_s(NULL, delim, &ptr);
	}
	return change;
}

BOOL ConnectToServer(SOCKET* serverSocket, char* host) {
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(HTTP_PORT);
	HOSTENT* hostent = gethostbyname(host);
	if (!hostent) {
		return FALSE;
	}
	in_addr Inaddr = *((in_addr*)*hostent->h_addr_list);
	serverAddr.sin_addr.s_addr = inet_addr(inet_ntoa(Inaddr));
	*serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (*serverSocket == INVALID_SOCKET) {
		return FALSE;
	}
	if (connect(*serverSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr))
		== SOCKET_ERROR) {
		closesocket(*serverSocket);
		return FALSE;
	}
	return TRUE;
}
BOOL Isequal(cache_HttpHeader htp1, HttpHeader htp2)
{
	if (strcmp(htp1.method, htp2.method)) return false;
	if (strcmp(htp1.url, htp2.url)) return false;
	if (strcmp(htp1.host, htp2.host)) return false;
	return true;
}

int Cache_find(__CACHE* cache, HttpHeader htp)
{
	int i = 0;
	for (i = 0; i < CACHE_MAXSIZE; i++)
	{
		if (Isequal(cache[i].htphed, htp)) return i;
	}
	return -1;
}