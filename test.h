#ifndef TEST_H
#define TEST_H

#define TEST(expr) (expr) ? fprintf(stderr, "\x1B[32mPASS:\033[0m %s", #expr) \
  : fprintf(stderr, "\x1B[31mFAIL:\033[0m %s", #expr); \
  fprintf(stderr, " at file %s, line %d\n", __FILE__, __LINE__)

#endif /* TEST_H */
