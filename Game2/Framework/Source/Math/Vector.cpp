#include "CoreHeaders.h"
#include "Vector.h"

namespace fw {

void vec2::Test()
{
    vec2 a(1,10);
    assert( a == vec2(1,10) );

    vec2 b(2,20);
    assert( b == vec2(2,20) );

    vec2 c = a + b;
    assert( c == vec2(3,30) );

    a += c;
    assert( a == vec2(4,40) );

    vec2 d = c;
    assert( d == vec2(3,30) );

    vec2 e( d );
    assert( e == vec2(3,30) );

    vec2 f = -e;
    assert( f == vec2(-3,-30) );

    float speed = 10.0f;
    float deltaTime = 1/60.0f;
    vec2 pos( 10, 5 );

    pos = speed * deltaTime * pos;
}

} // namespace fw
