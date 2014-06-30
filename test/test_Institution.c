#include "unity.h"
#include "Institution.h"
#include "mock_LinkedList.h"
#include "mock_Stack.h"
#include "CException.h"
#include "ErrorCode.h"

LinkedList inputList;
LinkedList outputList;
Stack stack;

Institution TARUC = {
						.name = "TARUC",
						.address = "Taman Bunga Raya",
						.postcode = 90712,
						.telephone = 01654325,
						.type = UniversityCollege,
						.yearEstablished = 1854
					};
Institution MMU = 	{
						.name = "MMU",
						.address = "Kuala Lumpur",
						.postcode = 90512,
						.telephone = 01327425,
						.type = University,
						.yearEstablished = 1742
					};
Institution UTAR = 	{	
						.name = "UTAR",
						.address = "Taman Bunga Raya",
						.postcode = 90502,
						.telephone = 01507025,
						.type = University,
						.yearEstablished = 2003
					};
void setUp(void){}

void tearDown(void){}

void test_Institution_reverse_given_TARUC_MMU_should_Push_TARUC_MMU_into_stack_and_Pop_return_2(void)
{
	int result;
	
	/*		Created a new stack		*/
	Stack_create_ExpectAndReturn(&stack);
	
	/*		Get data from LinkedList head and push into stack		*/
	List_removeHead_ExpectAndReturn(&inputList , &TARUC);
	Stack_push_Expect(&stack , &TARUC);
	List_removeHead_ExpectAndReturn(&inputList , &MMU);
	Stack_push_Expect(&stack , &MMU);
	List_removeHead_ExpectAndReturn(&inputList , NULL);
	Stack_push_Expect(&stack , NULL);
	
	/*		Pop data from stack and add into LinkedList tail		*/
	Stack_pop_ExpectAndReturn(&stack , &MMU);
	List_addTail_Expect(&outputList , &MMU);
	Stack_pop_ExpectAndReturn(&stack , &TARUC);
	List_addTail_Expect(&outputList , &TARUC);
	Stack_pop_ExpectAndReturn(&stack , NULL);
	List_addTail_Expect(&outputList , NULL);
	
	/*		store Institution_reverse into result
	*		2 indicate 2 element is reversed
	*/
	result = Institution_reverse(&inputList, &outputList);
	TEST_ASSERT_EQUAL(2 , result);
}

void test_Institution_reverse_given_TARUC_MMU_UTAR_should_Push_TARUC_MMU_UTAR_into_stack_and_Pop(void)
{
	int result;
	
	/*		Created a new stack		*/
	Stack_create_ExpectAndReturn(&stack);
	
	/*		Get data from LinkedList head and push into stack		*/
	List_removeHead_ExpectAndReturn(&inputList , &TARUC);
	Stack_push_Expect(&stack , &TARUC);
	List_removeHead_ExpectAndReturn(&inputList , &MMU);
	Stack_push_Expect(&stack , &MMU);
	List_removeHead_ExpectAndReturn(&inputList , &UTAR);
	Stack_push_Expect(&stack , &UTAR);
	List_removeHead_ExpectAndReturn(&inputList , NULL);
	Stack_push_Expect(&stack , NULL);
	
	/*		Pop data from stack and add into LinkedList tail		*/
	Stack_pop_ExpectAndReturn(&stack , &UTAR);
	List_addTail_Expect(&outputList , &UTAR);
	Stack_pop_ExpectAndReturn(&stack , &MMU);
	List_addTail_Expect(&outputList , &MMU);
	Stack_pop_ExpectAndReturn(&stack , &TARUC);
	List_addTail_Expect(&outputList , &TARUC);
	Stack_pop_ExpectAndReturn(&stack , NULL);
	List_addTail_Expect(&outputList , NULL);
	
	result = Institution_reverse(&inputList, &outputList);
	TEST_ASSERT_EQUAL(3 , result);
}

void test_isUniversityCollege_given_TARUC_UniversityCollege_should_return_1(void)
{
	int result = 0;
	
	result = isUniversityCollege((int*)TARUC.type , (int*)UniversityCollege);
	
	TEST_ASSERT_EQUAL(1 , result);
}

void test_isUniversityCollege_given_MMU_University_should_return_0(void)
{
	int result = 0;
	
	result = isUniversityCollege((int*)MMU.type , (int*)UniversityCollege);
	
	TEST_ASSERT_EQUAL(0 , result);
}

void test_Institution_select_given_TARUC_and_select_UniversityCollege_should_select_only_1(void)
{
	int result = 0;
	List_removeHead_ExpectAndReturn(&inputList , &TARUC);
	List_addTail_Expect(&outputList , &TARUC);
	List_removeHead_ExpectAndReturn(&inputList , NULL);
	
	result = Institution_select(&inputList,&outputList,(int*)UniversityCollege,isUniversityCollege);
	TEST_ASSERT_EQUAL(1 , result);
}

void test_Institution_select_given_TARUC_MMU_UTAR_and_select_University_should_select_2(void)
{
	int result = 0;
	List_removeHead_ExpectAndReturn(&inputList , &TARUC);
	List_removeHead_ExpectAndReturn(&inputList , &MMU);
	List_addTail_Expect(&outputList , &MMU);
	List_removeHead_ExpectAndReturn(&inputList , &UTAR);
	List_addTail_Expect(&outputList , &UTAR);
	List_removeHead_ExpectAndReturn(&inputList , NULL);

	result = Institution_select(&inputList,&outputList,(int*)University,isUniversityCollege);
	TEST_ASSERT_EQUAL(2 , result);
}

void test_wasEstablishedBefore_given_TARUC_1854year_should_return_1(void)
{
	int result = 0;
	int year = 1980;
	result = wasEstablishedBefore(&TARUC , &year);
	
	TEST_ASSERT_EQUAL(1 , result);
}

void test_wasEstablishedBefore_given_UTAR_2003year_should_return_0(void)
{
	int result = 0;
	int year = 1980;
	result = wasEstablishedBefore(&UTAR , &year);
	
	TEST_ASSERT_EQUAL(0 , result);
}

void test_wasEstablishedBefore_given_Aalto_2015year_should_throw_exception(void)
{
	Institution Aalto = {
							.name = "Aalto University",
							.address = "New York",
							.postcode = 90012,
							.telephone = 020654325,
							.type = University,
							.yearEstablished = 2015
							
						};
	int result = 0;
	int year = 1980;
	CEXCEPTION_T err;
	
	Try
	{
		result = wasEstablishedBefore(&Aalto , &year);
		TEST_FAIL_MESSAGE("Should throw ERR_INVALID_YEAR exception");
	}
	Catch(err)
	{
		TEST_ASSERT_EQUAL_MESSAGE(ERR_INVALID_YEAR , err , "Expect ERR_INVALID_YEAR exception");
		TEST_ASSERT_EQUAL(0 , result);
	}
}