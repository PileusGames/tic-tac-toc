/* file: minunit.h */

#ifndef TIC_TAC_TOC_MINUNIT_H
#define TIC_TAC_TOC_MINUNIT_H


#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; if (message) return message; } while (0)
extern int tests_run;

#endif //TIC_TAC_TOC_MINUNIT_H
