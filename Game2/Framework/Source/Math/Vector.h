#pragma once

namespace fw {

class vec2
{
public:
    vec2() : x(0), y(0) {}
    vec2(float nx, float ny) : x(nx), y(ny) {}

    static void Test();

    void Set(float nx, float ny) { x = nx; y = ny; }

    inline vec2 operator+(const vec2& o) const { return vec2( x+o.x, y+o.y ); }
    inline vec2 operator-(const vec2& o) const { return vec2( x-o.x, y-o.y ); }
    inline vec2 operator*(const vec2& o) const { return vec2( x*o.x, y*o.y ); }
    inline vec2 operator/(const vec2& o) const { return vec2( x/o.x, y/o.y ); }

    inline vec2 operator*(float o) const { return vec2( x*o, y*o ); }
    inline vec2 operator/(float o) const { return vec2( x/o, y/o ); }

    inline vec2& operator+=(const vec2& o) { x += o.x; y += o.y; return *this; }
    inline vec2& operator-=(const vec2& o) { x -= o.x; y -= o.y; return *this; }
    inline vec2& operator*=(const vec2& o) { x *= o.x; y *= o.y; return *this; }
    inline vec2& operator/=(const vec2& o) { x /= o.x; y /= o.y; return *this; }

    inline bool operator==(const vec2& o) const { return ( x == o.x && y == o.y ); }
    inline bool operator!=(const vec2& o) const { return ( x != o.x || y != o.y ); }

    inline vec2 operator-() const { return vec2(-x, -y); }

    float Length() const
    {
        return sqrtf( x*x + y*y );
    }

    float DistanceTo(const vec2& o) const
    {
        return (*this - o).Length();
    }

    void Normalize()
    {
        if( x != 0 || y != 0 )
        {
            float len = Length();
            x /= len;
            y /= len;
        }
    }

    vec2 GetNormalized() const
    {
        if( x != 0 || y != 0 )
        {
            float len = Length();
            return vec2( x/len, y/len );
        }

        return vec2(0,0);
    }

    float Dot(const vec2& o) const
    {
        return x*o.x + y*o.y;
    }

    float AngleRadians()
    {
        return atan2f( y, x );
    }

    float AngleFromRadians(const vec2& o) const
    {
        assert( false ); // TEST THIS CODE!!!!!

        float a1 = atan2f( y, x );
        float a2 = atan2f( o.y, o.x );

        float diff = a2 - a1;

        // TODO: Actually test in all quadrants.
        if( diff > 3.1415927f )
            diff = -2*3.1415927f + diff;
        if( diff < -3.1415927f )
            diff = 2*3.1415927f - diff;

        return diff;
    }

public:
    float x;
    float y;
};

inline vec2 operator*(float f, const vec2& v) { return vec2(f*v.x, f*v.y); }

} // namespace fw
