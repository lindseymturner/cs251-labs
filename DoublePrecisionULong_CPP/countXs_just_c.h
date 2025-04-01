//
// Created by davew on 6/27/23.
//

#ifndef BIGINT_COUNTXS_JUST_C_H
#define BIGINT_COUNTXS_JUST_C_H

#if defined __cplusplus  /* read this "extern C" line _only_ when we're using C++ */
extern "C" {
#endif

int countXs_just_c(const char s[ ]); // s is a C-style array of characters, we assume terminated by a NULL ('\n')

#if defined __cplusplus  /* match (with "}" that "extern C" line _only_ when we're using C++ */
};
#endif


#endif //BIGINT_COUNTXS_JUST_C_H
