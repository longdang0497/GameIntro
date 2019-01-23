
#include "trace.h"

static const char* PATH = TRACE_LOG_PATH;
int traceFlag = 1;

void trace(const LPCWSTR format, ...)
{
	if (!traceFlag) return;

	FILE *f = stderr;

	if (PATH != NULL)
	{
		if (fopen_s(&f, PATH, "a") != 0)
		{
			fprintf(stderr, "WARNING: Failed to open trace file '%s' for writing!\n", PATH);
			return;
		}
	}


	va_list ap;
	va_start(ap, format);
	vfwprintf(f, format, ap);
	va_end(ap);

	fprintf(f, "\n==========\n");

	if (PATH != NULL) fclose(f);
}