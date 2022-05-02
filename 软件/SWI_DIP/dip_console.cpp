#include "SWI_DIP.h"

void Info(const char* text) {
	printf_s("[INFO]%s\n", text);
}
void Warn(const char* text) {
	printf_s("[WARN]%s\n", text);
}
void Error(const char* text) {
	printf_s("[ERROR]%s\n", text);
}
void Send(const char* code) {
	printf_s("[SEND]{%s}\n", code);
}
void Send(const char* code, const char* content) {
	printf_s("[SEND]{%s}(%s)\n", code, content);
}
void Respond(bool ans) {
	if (ans)
		printf_s("[RESPOND]{YES}\n");
	else
		printf_s("[RESPOND]{NO}\n");
}