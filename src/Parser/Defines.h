#ifndef eatToken
#define eatToken(...)                       \
    if (!tryToEatToken(__VA_ARGS__))        \
        [[unlikely]]                        \
        {                                   \
            generateErrorText(__VA_ARGS__); \
            return NULL;                    \
        }
#endif

#ifndef softAssertNode
#define softAssertNode(x) \
    if (!x)               \
        [[unlikely]]      \
        {                 \
            return NULL;  \
        }
#endif