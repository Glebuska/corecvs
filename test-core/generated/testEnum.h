#ifndef TEST_ENUM_H_
#define TEST_ENUM_H_
/**
 * \file testEnum.h
 * \attention This file is automatically generated and should not be in general modified manually
 *
 * \date MMM DD, 20YY
 * \author autoGenerator
 * Generated from test.xml
 */

/**
 * Helper namespace to hide TestEnum enum from global context.
 */

namespace TestEnum {

/** 
 * \brief Test Enum 
 * Test Enum 
 */
enum TestEnum {
    /** 
     * \brief item1 
     * item1 
     */
    ITEM1 = 0,
    /** 
     * \brief item2 
     * item2 
     */
    ITEM2 = 1,
    /** 
     * \brief itemWithIcon 
     * itemWithIcon 
     */
    ITEMWITHICON = 2,
    /** 
     * \brief Last virtual option to run cycles to
     */
    TEST_ENUM_LAST
};


static inline const char *getName(const TestEnum &value)
{
    switch (value) 
    {
     case ITEM1 : return "ITEM1"; break ;
     case ITEM2 : return "ITEM2"; break ;
     case ITEMWITHICON : return "ITEMWITHICON"; break ;
     default : return "Not in range"; break ;
     
    }
    return "Not in range";
}

} //namespace TestEnum

#endif  //TEST_ENUM_H_