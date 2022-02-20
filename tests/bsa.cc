#include <assert.h>
#include <stdint.h>

class Timestamp
{
private:
    int64_t microSecondsSinceEpoch_; 
};

static_assert(sizeof(int64_t) == sizeof(Timestamp));

int main()
{
    
    return 0;
}