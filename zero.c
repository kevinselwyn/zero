#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

#if !defined(__APPLE__)
#include <malloc.h>
#endif

#define NAME "VR-suit MARK-1 ALPHA 1.0.0.1.12.2333.43.129.1"
#define TITLE_TRUE  'X'
#define TITLE_FALSE ' '
#define MAN_TRUE    '.'
#define MAN_FALSE   '0'

#define TITLE_MAX 47
#define MAN_MAX   49
#define MAN_MIN   19
#define MAN_PARTS 11
#define TITLE_SEQ 5
#define MAN_SEQ   25
#define SLEEP     50000

long title[TITLE_SEQ] = {
	0x11701D2EE062, 0x114821244094, 0xA7399244E98,0xA5005244099, 0x44839EE4066
};

long man[MAN_PARTS] = {
	522495, 520319, 516159, 491535, 262145, 0,
	16400, 311321, 508447, 517951, 524287
};

char man_sequence[MAN_SEQ] = "012103456666678888888889";

int title2string(char *line, long title) {
	int rc = 0, i = 0, l = 0, counter = 0;

	for (i = TITLE_MAX - 1, l = 0; i >= l; i--) {
		line[counter++] = (title & (long)pow(2, i)) ? TITLE_TRUE : TITLE_FALSE;
	}

	line[counter] = '\0';

	return rc;
}

int man2string(char *line, long man) {
	int rc = 0, i = 0, l = 0, counter = 0;
	size_t length = 0;
	char *output = NULL, *pad = NULL;

	output = malloc(sizeof(char) * 20);

	if (!output) {
		printf("Memory error\n");

		rc = 1;
		goto cleanup;
	}

	for (i = MAN_MIN - 1, l = 0; i >= l; i--) {
		output[counter++] = (man & (long)pow(2, i)) ? MAN_TRUE : MAN_FALSE;
	}

	output[counter] = '\0';
	length = floor((MAN_MAX - strlen(output)) / 2);
	counter = 0;

	pad = malloc(sizeof(char) * length + 1);

	if (!pad) {
		printf("Memory error\n");

		rc = 1;
		goto cleanup;
	}

	for (i = 0, l = length; i < l; i++) {
		pad[counter++] = MAN_TRUE;
	}

	pad[counter] = '\0';

	strcpy(line, pad);
	strcat(line, output);
	strcat(line, pad);

cleanup:
	if (output) {
		free(output);
	}

	if (pad) {
		free(pad);
	}

	return rc;
}

int main() {
	int rc = 0, i = 0, l = 0, seq = 0;
	char *line = NULL;

	line = malloc(sizeof(char) * MAN_MAX + 1);

	if (!line) {
		printf("Memory error\n");

		rc = 1;
		goto cleanup;
	}

	system("clear");

	printf("  %s\n\n", NAME);

	for (i = 0, l = TITLE_SEQ; i < l; i++) {
		rc = title2string(line, title[i]);

		if (rc) {
			goto cleanup;
		}

		printf("%s\n", line);
	}

	printf("\n");

	usleep(SLEEP * 10);

	for (i = 0, l = MAN_SEQ - 1; i < l; i++) {
		seq = (i != MAN_SEQ - 2) ? man_sequence[i] - '0' : MAN_PARTS - 1;
		rc = man2string(line, man[seq]);

		if (rc) {
			goto cleanup;
		}

		printf("%s\n", line);
		usleep(SLEEP);
	}

cleanup:
	if (line) {
		free(line);
	}

	return rc;
}