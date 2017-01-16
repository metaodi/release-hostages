#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int units = 10;
int anzhost = 7;
int max_days = 500;
int runs = 100;
int show = 0;
int pause_time = 0;
char commit = 'n';

void usage(char *prog) {
	fprintf(
			stderr,
			"\n%s usage:\t%s\t"
				"-u units, number of days to keep track (DEFAULT: 7)\n"
				"\t\t\t\t\t-h number of hostages (DEFAULT: 10)\n"
				"\t\t\t\t\t-d maximum days (DEFAULT: 500)\n"
				"\t\t\t\t\t-r runs (DEFAULT: 100)\n"
				"\t\t\t\t\t-c require commit for certain types (DEFAULT: n) [possible types: a(ll), s(uccess) only, m(issed) only, n(one)]\n"
				"\t\t\t\t\t-s show mode (DEFAULT: 0)\n\n\t-->"
				"If you call -s without a time parameter it uses the default pause,\n\tbut enables the show mode. (!!THIS MUST BE THE LAST ARGUMENT!!)\n\t is on MS Windows in milliseconds and on Linux in seconds (afaik)\n"
				"\n\nIf you call %s without arguments, the default values will be taken.\n",
			prog, prog, prog);

	printf("\n\n\t\t\t\t\t\t\t\t\t\t\t\t\tby 0di 2oo4\n\n");
}

int options(int argc, char *argv[]) {
	if (argc == 1) {
		printf("\n\nUSE\n\t\t%s -H OR\n\t\t%s /?\nfor HELP\n\n", argv[0],
				argv[0]);
	}

	if (argc > 13) {
		fprintf(stderr, "!!! too many arguments !!!\n");

		exit(0);

	}

	int i;

	for (i = 1; i < argc; i++) {
		switch (argv[i][1]) {
		case 'H':
		case '?': {
			usage(argv[0]);
			exit(0);
		}
			break;
		case 'u': {
			if (argv[i + 1]) {
				units = atoi(argv[i + 1]);
				i++;
				break;
			}
			break;
		}
		case 'h': {
			if (argv[i + 1]) {
				anzhost = atoi(argv[i + 1]);
				i++;
				break;
			}
			break;
		}
		case 'd': {
			if (argv[i + 1]) {
				max_days = atoi(argv[i + 1]);
				i++;
				break;

			}
			break;
		}
		case 'r': {
			if (argv[i + 1]) {
				runs = atoi(argv[i + 1]);
				i++;
				break;
			}
			break;
		}

		case 's': {
			show = 1;

			if (argv[i + 1]) {
				pause_time = atoi(argv[i + 1]);

				printf("SHOW MODE ON\nPAUSE: %i\n", pause_time);

				i++;

				break;

			}
			break;

		}

		case 'c': {
			if (argv[i + 1]) {
				commit = argv[i + 1][0];

				i++;

				break;

			}
			break;

		}

		default:
			fprintf(stderr, "unknown option %s\n", argv[i]);
			usage(argv[0]);
			exit(0);
			break;

		}
	}

	printf("RUNS: %i\n", runs);
	printf("UNITS: %i\n", units);
	printf("HOSTAGES: %i\n", anzhost);
	printf("MAX_DAYS: %i\n", max_days);
	printf("COMMIT: %c\n", commit);

	if (show == 1) {
		printf("SHOW MODE: ON\n");

		printf("PAUSE: %i", pause_time);

	} else {
		printf("SHOW MODE: OFF");
	}

	return 0;

}

int main(int argc, char *argv[]) {

	options(argc, argv);

	int host_know[anzhost][units];
	//Remember the knowledge of each hostage
	int dayc;
	//Count the total days
	int unitc;
	//Count the Units (weeks), initalise with 0, so the game begins in the 0th week (unit)
	int hostunit;
	//Hostage Unit
	int light;
	//The light is off at the beginning
	int release;
	//If the hostages could be released this si set to 1

	int x, y, z;

	int hod;
	//Number of the "Hostage of the day"
	int miss = 0;
	//Counts all missed runs
	int suc = 0;
	//Counts successful runs
	float sucper, missper;
	//stores the percent of suc and miss (relative to runs)
	int days[runs];
	//Counts how many days it took for a successful run

	//Initialize Day-Array with 0
	for (x = 0; x < runs; x++) {
		days[x] = 0;

	}

	//Hostages are named like that: 0-6, therefore the weeks (UNITS) are also 0-6 or higher, depeneding on the constance values.

	//Choose the HOD (hostage of the day :-) ) --> Number between 0 and 6;

	//Turn on the light if it's the unit of the hostage.

	//Add Knowledge to the hostage (Check the week and check if the light is on). Check if the hostage has enought knowlegde to win the game
	//WARNING: DON'T DELETE ANY KNOWLEDGE!!!

	//Make rand() more random
	srand(time(NULL));

	//Increase runs to get the user wished result... (1 of n instead of 0 of n) and to get the correct iteration number
	runs++;

	for (y = 1; y < runs; y++) {
		x = 0;

		z = 0;

		release = 0;

		light = 0;

		hostunit = 0;

		unitc = 0;

		dayc = 0;

		//Initalise Knowledege (nobody knows anything ;-) )
		while (x < anzhost) {
			while (z < units) {
				host_know[x][z] = 0;

				z++;

			}
			x++;

			z = 0;

		}

		while (dayc < max_days) {
			if (release == 1) {
				break;

			}

			//If a new Unit begins, reset the light and increase the unit counters
			if (dayc % units == 0) {
				hostunit++;

				unitc++;

				light = 0;

			}
			dayc++;

			if (hostunit == anzhost) {
				hostunit = 0;

			}

			//It's more randomly if you pass a pseudo random number to srand (the System time in this case)
			//After that you can call rand() which should be more randomly...

			hod = rand() % anzhost;

			//Turn on the light if it's the HOU (Hostage of the Unit[Week]).
			if (hostunit == hod) {
				light = 1;

			}

			//If the light is turned on, the knowledge of the HUD will increase
			if (light == 1) {
				host_know[hod][hostunit] = 1;

			}

			//Check if the knowledge is as big as he can release all hostages
			x = 0;

			while (x < units) {
				if (host_know[hod][x] == 1) {
					x++;

				}
				//If the HOD has no info about one other hostage, the test will fail
				else
					break;

				if (x == 7) {
					suc++;

					days[y] = dayc;

					release = 1;

				}
			}

			if (show == 1) {
				//Print Status of each day
				runs--;

				printf(
						"Current Hostage:\t%i\nHostage Unit:\t\t%i\nUNITS:\t\t\t%i\nTotal Days:\t\t%i\nLIGHT:\t\t\t%i\t\t\t\tHOD(%i): %i %i %i %i %i %i %i\nRUN: %i of %i\n\n",
						hod, hostunit, unitc, dayc, light, hod,
						host_know[hod][0], host_know[hod][1],
						host_know[hod][2], host_know[hod][3],
						host_know[hod][4], host_know[hod][5],
						host_know[hod][6], y, runs);

				runs++;

				//Sleep 1 second (1000 millisecond [MS WINDOWS style]), to get surely a random number (time(NULL))
				sleep(pause_time);

			}

			//Print out SUCCESS-Message
			if (release == 1) {
				printf(
						"\n\nHOSTAGES WERE RELEASED!!! After %i days (%i. run)\n\n",
						dayc, y);

				if (commit == 's' || commit == 'a') {
					char line[1024];
					printf("\n[Press Enter to continue]\n");
					scanf("%[^\n]", line);
				}
			}

		}

		//Count the tries where the hostages won't be released within "max_tries" times
		if (release != 1) {
			miss++;

			printf(
					"MISSED! The Hostage weren't released within %i days (%i. run)\n\n",
					max_days, y);

			if (commit == 'm' || commit == 'a') {
				system("pause");

			}
			dayc = max_days;

		}
	}

	//If there are no successful runs, there are no days to count
	if (suc > 0) {
		//Reset the day counter to reuse it for some other purpose
		dayc = 0;

		//Count all days for every release
		for (x = 0; x < runs; x++) {
			if (days[x] > 0) {
				dayc = dayc + days[x];
			}

		}

		//Calculate the average
		dayc = dayc / suc;

	}

	//Calucalte the percent of success and miss
	//runs = 100%
	runs--;
	//Correct the Display-Fake from above

	missper = miss * 100 / runs;

	sucper = suc * 100 / runs;

	//Print out the FAZIT
	printf("\n\n\n------------------TOTAL-------------------------------");

	printf(
			"\n\nMISS: %i (%f %%)\n\nSUCCESS: %i (%f %%)\n\n\nAverage days: %i\n\n\n",
			miss, missper, suc, sucper, dayc);

	return 0;

}
