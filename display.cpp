#include "display.h"
void usage()
{
    char output[MaxOutput];
    int ret = snprintf(output, MaxOutput,
        "\t%s\n\t%s\n\t%s\n\t%s\n",
        "[usage]",
        "[-s]   sleep or wake up now"
        "[-w]   start or stop work/study now"
        "[-p]   start or stop play telephone now"
        );
    if (ret > 0)
        printf("%s", output);
    else
        printf("%s", "The usage is wrong\n");
}