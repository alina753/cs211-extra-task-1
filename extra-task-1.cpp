
#include <assert.h>
double seconds_difference(double time_1, double time_2)
{
    return (time_2 - time_1);
}

double hours_difference(double time_1, double time_2)
{
    return (seconds_difference(time_1, time_2) / 3600);
}

double to_float_hours(int hours, int minutes, int seconds)
{
    assert((minutes < 60) & (minutes >= 0));
    assert((seconds < 60) & (seconds >= 0));
    return ((seconds + (minutes * 60)) / 3600.0 + hours);
}

double to_24_hour_clock(double hours)
{
    assert(hours >= 0);
    int a = hours / 24;
    return hours - (a * 24);
}
int get_hours(int sec)
{
    return sec / 3600 % 24;
}

int get_minutes(int sec)
{
    return sec / 60 % 60;
}

int get_seconds(int sec)
{
    return sec % 60;
}

double time_to_utc(int utc_offset, double time)
{
    assert(time >= 0);
    double c = time - utc_offset;
    return (c >= 24) ? c - 24 : c;
}

double time_from_utc(int utc_offset, double time)
{
    assert(time >= 0);
    double c = time + utc_offset;
    if (c < 0)
        return 24 + c;
    if (c >= 24)
        return   c - 24;
    else return c;
}

int main()
{
    assert(seconds_difference(1800.0, 3600.0) == 1800.0);
    assert(seconds_difference(3600.0, 1800.0) == -1800.0);
    assert(seconds_difference(1800.0, 2160.0) == 360.0);
    assert(seconds_difference(1800.0, 1800.0) == 0.0);

    assert(hours_difference(1800.0, 3600.0) == 0.5);
    assert(hours_difference(3600.0, 1800.0) == -0.5);
    assert(hours_difference(1800.0, 2160.0) == 0.1);
    assert(hours_difference(1800.0, 1800.0) == 0.0);

    assert(to_float_hours(0, 15, 0) == 0.25);
    assert(to_float_hours(2, 45, 9) == 2.7525);
    assert(to_float_hours(1, 0, 36) == 1.01);

    assert(to_24_hour_clock(24) == 0);
    assert(to_24_hour_clock(48) == 0);
    assert(to_24_hour_clock(25) == 1);
    assert(to_24_hour_clock(4) == 4);
    assert(to_24_hour_clock(28.5) == 4.5);

    assert(get_hours(3800) == 1);
    assert(get_minutes(3800) == 3);
    assert(get_seconds(3800) == 20);

    assert(time_to_utc(+0, 12.0) == 12.0);
    assert(time_to_utc(+1, 12.0) == 11.0);
    assert(time_to_utc(-1, 12.0) == 13.0);
    assert(time_to_utc(-11, 18.0) == 5.0);
    assert(time_to_utc(-1, 0.0) == 1.0);
    assert(time_to_utc(-1, 23.0) == 0.0);

    assert(time_from_utc(+0, 12.0) == 12.0);
    assert(time_from_utc(+1, 12.0) == 13.0);
    assert(time_from_utc(-1, 12.0) == 11.0);
    assert(time_from_utc(+6, 6.0) == 12.0);
    assert(time_from_utc(-7, 6.0) == 23.0);
    assert(time_from_utc(-1, 0.0) == 23.0);
    assert(time_from_utc(-1, 23.0) == 22.0);
    assert(time_from_utc(+1, 23.0) == 0.0);
}