#ifndef TYPES_H
#define TYPES_H

typedef enum
{
    m_success,
    m_failure
} Status;

typedef enum
{
    t,
    a,
    A,
    y,
    m,
    c
}etags;


typedef enum
{
    m_title,
    m_album,
    m_artist,
    m_year,
    m_contentType,
    m_comment
}vtags;

#endif