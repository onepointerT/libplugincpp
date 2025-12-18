// Copyright 2025 The OnePointer Authors.
//

#include "cpptime.hpp"

#include <cstring>


namespace plugin {
namespace util {


TimeTag* TimeTag::parse_time( const std::string tflag ) {
    TimeTag* tt = new TimeTag();

    sscanf( tflag.c_str(), "%u-%u-%u\/%u:%u:%u", tt->year, tt->month, tt->day
                                               , tt->hours, tt->minutes, tt->seconds );
    
    return tt;
}


TimeTag::TimeTag()
    :   year( 0 )
    ,   month( 0 )
    ,   day( 0 )
    ,   hours( 0 )
    ,   minutes( 0 )
    ,   seconds( 0 )
{}

TimeTag::TimeTag( const std::string tflag )
    :   year( 0 )
    ,   month( 0 )
    ,   day( 0 )
    ,   hours( 0 )
    ,   minutes( 0 )
    ,   seconds( 0 )
{
    TimeTag* tt = TimeTag::parse_time( tflag );
    if ( tt != nullptr ) {
        this->year = tt->year;
        this->month = tt->month;
        this->day = tt->day;
        this->hours = tt->hours;
        this->minutes = tt->minutes;
        this->seconds = tt->seconds;
    }
}

TimeTag::TimeTag( const uint8_t hours, const uint8_t minutes, const uint8_t seconds )
    :   year( 0 )
    ,   month( 0 )
    ,   day( 0 )
    ,   hours( hours )
    ,   minutes( minutes )
    ,   seconds( seconds )
{}

TimeTag::TimeTag( const uint8_t year, const uint8_t month, const uint8_t day )
    :   year( year )
    ,   month( month )
    ,   day( day )
    ,   hours( 0 )
    ,   minutes( 0 )
    ,   seconds( 0 )
{}

TimeTag::TimeTag( const uint8_t year, const uint8_t month, const uint8_t day
        , const uint8_t hours, const uint8_t minutes, const uint8_t seconds
)   :   year( year )
    ,   month( month )
    ,   day( day )
    ,   hours( hours )
    ,   minutes( minutes )
    ,   seconds( seconds )
{}

TimeTag::operator std::string() const {
    char* timestr = new char[19];

    sprintf( timestr, "%s-%s-%s\/%s:%s:%s", this->year, this->month, this->day
                                        , this->hours, this->minutes, this->seconds );
    
    return timestr;
}

TimeTag& TimeTag::operator+=( const TimeTag& another ) {
    this->operator+( *this, another );
    return *this;
}


uint8_t TimeTag::plus_month( const uint8_t lhs, const uint8_t rhs, TimeTag& initial ) {
    TimeTag* tt = &initial;

    if ( lhs + rhs > 12 ) {
        uint8_t years_add = (lhs % 12) + (rhs % 12);
        years_add += ((lhs + rhs) % 12) - years_add;
        tt->year += years_add;
        tt->month += lhs - ((lhs % 12)*12) + rhs - ((rhs % 12)*12);
    } else tt->month = lhs + rhs;

    return tt->month;
}


uint8_t TimeTag::plus_day( const uint8_t lhs, const uint8_t rhs, TimeTag& initial ) {
    TimeTag* tt = &initial;

    if ( lhs + rhs > 31 ) {
        uint8_t months_add = (lhs % 31) + (rhs % 31);
        months_add += ((lhs + rhs) % 31) - months_add;
        TimeTag::plus_month( tt->month, months_add, *tt );
        tt->day += lhs - ((lhs % 31)*31) + rhs - ((rhs % 31)*31);
    } else tt->day = lhs + rhs;

    return tt->day;
}


uint8_t TimeTag::plus_hours( const uint8_t lhs, const uint8_t rhs, TimeTag& initial ) {
    TimeTag* tt = &initial;

    if ( lhs + rhs > 24 ) {
        uint8_t days_plus = (lhs % 24) + (rhs % 24);
        days_plus += ((lhs + rhs) % 24) - days_plus;
        TimeTag::plus_day( tt->day, days_plus, *tt );
        tt->hours += lhs - ((lhs % 24)*24) + rhs - ((rhs % 24)*24);
    } else tt->hours = lhs + rhs;

    return tt->hours;
}


uint8_t TimeTag::plus_minutes( const uint8_t lhs, const uint8_t rhs, TimeTag& initial ) {
    TimeTag* tt = &initial;

    if ( lhs + rhs > 60 ) {
        uint8_t hours_plus = (lhs % 60) + (rhs % 60);
        hours_plus += ((lhs + rhs) % 60) - hours_plus;
        TimeTag::plus_hours( tt->hours, hours_plus, *tt );
        tt->minutes += lhs - ((lhs % 60)*60) + rhs - ((rhs % 60)*60);
    } else tt->minutes = lhs + rhs;

    return tt->minutes;
}


uint8_t TimeTag::plus_seconds( const uint8_t lhs, const uint8_t rhs, TimeTag& initial ) {
    TimeTag* tt = &initial;

    if ( lhs + rhs > 60 ) {
        uint8_t minutes_plus = (lhs % 60) + (rhs % 60);
        minutes_plus += ((lhs + rhs) % 60) - minutes_plus;
        TimeTag::plus_minutes( tt->hours, minutes_plus, *tt );
        tt->minutes += lhs - ((lhs % 60)*60) + rhs - ((rhs % 60)*60);
    } else tt->minutes = lhs + rhs;

    return tt->minutes;
}

TimeTag TimeTag::operator+( const TimeTag& lhs, const TimeTag& rhs ) {
    TimeTag* tt = new TimeTag();

    tt->year = lhs.year + rhs.year;
    tt->month = TimeTag::plus_month( lhs.month, rhs.month, *tt );
    tt->day = TimeTag::plus_day( lhs.day, rhs.day, *tt );
    tt->hours = TimeTag::plus_hours( lhs.hours, rhs.hours, *tt );
    tt->minutes = TimeTag::plus_minutes( lhs.minutes, rhs.minutes, *tt );
    tt->seconds = TimeTag::plus_seconds( lhs.seconds, rhs.seconds, *tt );

    return *tt;
}


} // namespace util
} // namespace plugin
