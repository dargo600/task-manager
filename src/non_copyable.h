#ifndef NON_COPYABLE_H
#define NON_COPYABLE_H

class NonCopyable {
   public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    ~NonCopyable() = default;
};

#endif