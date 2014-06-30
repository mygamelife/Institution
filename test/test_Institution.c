#include "unity.h"
#include "Institution.h"
#include "mock_LinkedList.h"
#include "mock_Stack.h"

LinkedList list;
LinkedList inputList;
LinkedList outputList;
Stack stack;
	
void setUp(void)
{}

void tearDown(void)
{}

void test_Institution_reverse(void)
{	
	Institution TARUC = {
							.name = "TARUC",
							.address = "TBR",
							.postcode = 9072,
							.telephone = 0111111,
							.type = UniversityCollege,
							.yearEstablished = 1859
						};
						
	Institution UTAR = 	{
							.name = "UTAR",
							.address = "TBR",
							.postcode = 9070,
							.telephone = 0134111,
							.type = University,
							.yearEstablished = 2003
						};
						
	Institution MMU = 	{
							.name = "MMU",
							.address = "KualaLumpur",
							.postcode = 9570,
							.telephone = 0534111,
							.type = University,
							.yearEstablished = 1784
						};

	Stack_create_ExpectAndReturn(&stack);
	
	List_removeHead_ExpectAndReturn(&list,&TARUC);
	Stack_push_Expect(&stack,&TARUC);
	List_removeHead_ExpectAndReturn(&list,&UTAR);
	Stack_push_Expect(&stack,&UTAR);
	List_removeHead_ExpectAndReturn(&list,&MMU);
	Stack_push_Expect(&stack,&MMU);
	List_removeHead_ExpectAndReturn(&list,NULL);
	Stack_push_Expect(&stack,NULL);
	
	Stack_pop_ExpectAndReturn(&stack,&MMU);
	List_addTail_Expect(&list,&MMU);
	Stack_pop_ExpectAndReturn(&stack,&UTAR);
	List_addTail_Expect(&list,&UTAR);
	Stack_pop_ExpectAndReturn(&stack,&TARUC);
	List_addTail_Expect(&list,&TARUC);
	Stack_pop_ExpectAndReturn(&stack,NULL);
	List_addTail_Expect(&list,NULL);
	
	Institution_reverse(&inputList, &outputList);
}

void test_isUniversity(void)
{
	Institution TARUC = {
							.name = "TARUC",
							.address = "TBR",
							.postcode = 9072,
							.telephone = 0111111,
							.type = UniversityCollege,
							.yearEstablished = 1859
						};
						
	Institution UTAR = 	{
							.name = "UTAR",
							.address = "TBR",
							.postcode = 9070,
							.telephone = 0134111,
							.type = University,
							.yearEstablished = 2003
						};
						
	Institution MMU = 	{
							.name = "MMU",
							.address = "KualaLumpur",
							.postcode = 9570,
							.telephone = 0534111,
							.type = University,
							.yearEstablished = 1784
						};
	int result = 0;
	result = isUniversityCollege ((int*)UTAR.type , (int*)UniversityCollege);
}

void test_Institution_select(void)
{
	Institution TARUC = {
							.name = "TARUC",
							.address = "TBR",
							.postcode = 9072,
							.telephone = 0111111,
							.type = UniversityCollege,
							.yearEstablished = 1859
						};
						
	Institution UTAR = 	{
							.name = "UTAR",
							.address = "TBR",
							.postcode = 9070,
							.telephone = 0134111,
							.type = University,
							.yearEstablished = 2003
						};
						
	Institution MMU = 	{
							.name = "MMU",
							.address = "KualaLumpur",
							.postcode = 9570,
							.telephone = 0534111,
							.type = University,
							.yearEstablished = 1784
						};
	int result = 0 ;
	List_removeHead_ExpectAndReturn(&inputList,&TARUC);
	List_removeHead_ExpectAndReturn(&inputList,&UTAR);
	List_removeHead_ExpectAndReturn(&inputList,&MMU);
	
	result = Institution_select(&inputList,&outputList,(int*)UniversityCollege,isUniversityCollege);
}