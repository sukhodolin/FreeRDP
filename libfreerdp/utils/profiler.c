/**
 * FreeRDP: A Remote Desktop Protocol Implementation
 * Profiler Utils
 *
 * Copyright 2011 Stephen Erisman
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>

#include <freerdp/utils/profiler.h>

PROFILER* profiler_create(char* name)
{
	PROFILER* profiler;

	profiler = (PROFILER*) malloc(sizeof(PROFILER));
	
	profiler->name = name;
	profiler->stopwatch = stopwatch_create();

	return profiler;
}

void profiler_free(PROFILER* profiler)
{	
	stopwatch_free(profiler->stopwatch);
	
	free(profiler);
}

void profiler_enter(PROFILER* profiler)
{
	stopwatch_start(profiler->stopwatch);
}

void profiler_exit(PROFILER* profiler)
{
	stopwatch_stop(profiler->stopwatch);
}

void profiler_print_header()
{
	fprintf(stderr, "\n");
	fprintf(stderr, "                                             |-----------------------|\n" );
	fprintf(stderr, "                PROFILER                     |    elapsed seconds    |\n" );
	fprintf(stderr, "|--------------------------------------------|-----------------------|\n" );
	fprintf(stderr, "| code section                  | iterations |     total |      avg. |\n" );
	fprintf(stderr, "|-------------------------------|------------|-----------|-----------|\n" );
}

void profiler_print(PROFILER* profiler)
{
	double elapsed_sec = stopwatch_get_elapsed_time_in_seconds(profiler->stopwatch);
	double avg_sec = elapsed_sec / (double) profiler->stopwatch->count;
	
	fprintf(stderr, "| %-30.30s| %10lu | %9f | %9f |\n", profiler->name, profiler->stopwatch->count, elapsed_sec, avg_sec);
}

void profiler_print_footer()
{
	fprintf(stderr, "|--------------------------------------------------------------------|\n" );
}
