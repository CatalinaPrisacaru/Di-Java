/*******************************************************************************

  Sample file: EGSTRUCT1.C

  Objective: Shows how to access node records in an OpenFlight database.  
     Shows the structure of an OpenFlight database.  
	  Shows how to use various other OpenFlight API structure library routines.

  Program functions: Open a database from command line.  
     Manually traverse the database from the top record down to the first
        object record.  
	  Print the names of the object record's parent, child, previous, and 
	     next records.
	  Auto traverse (mgWalk) the database and print all the node records that 
	     have nested children.
	  Get the file name from the object record.

  API functions used:
     mgInit(), mgExit(), mgFree(), mgGetLastError(),
	  mgGetNext(), mgGetPrevious(), mgGetParent(), 
     mgGetNestedParent(), mgGetNestedChild(), 
     mgGetChild(), mgGetChildNth(), mgIsCode(),
	  mgRec2Filename(), mgCountChild(), mgGetName(),
	  mgWalk(), mgOpenDb(), mgCloseDb()

 ******************************************************************************/
	
#include <stdlib.h>
#include <stdio.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

static mgbool FindNested (mgrec* db, mgrec* par, mgrec* rec, void* userData)
{
	mgrec* nestedRec;

	/* if find record with nested child, print name */
	/* of record and nested child */
	if ((nestedRec = mgGetNestedChild (rec)) != MG_NULL) {
		if (mgGetNestedParent (nestedRec) != rec) {
			printf ("there was a nested record problem\n");
			exit (EXIT_FAILURE);
		}
		else {
			char* name = mgGetName (rec);
			char* nestedName = mgGetName (nestedRec);
			printf ("   %s has nested child : %s\n", name, nestedName);
			mgFree (name);
			mgFree (nestedName); /* mgGetName allocs, user must dealloc */
		}
	}
	return (MG_TRUE);
}

static void PrintAdjacent (mgrec* rec)
/* prints the names of a node record's parent, 1st child, previous, next, etc. */
{
	char* childname = MG_NULL;
	char* objname = MG_NULL;
	char* parname = MG_NULL;
	char* prevname = MG_NULL;
	char* nextname = MG_NULL;
	char* childnthname = MG_NULL;
	int numChildren = mgCountChild(rec);

	objname = mgGetName (rec);
	parname = mgGetName (mgGetParent(rec));
	childname = mgGetName (mgGetChild(rec));
	prevname = mgGetName (mgGetPrevious(rec));
	nextname = mgGetName (mgGetNext(rec));
	childnthname = (numChildren >= 2) ? mgGetName (mgGetChildNth(rec, 2)) : MG_NULL;

	printf ("Node Name : %s\n", objname   ? objname   : "None");
	printf ("Parent    : %s\n", parname   ? parname   : "None"); 
	printf ("1st child : %s\n", childname ? childname : "None"); 
	printf ("Previous  : %s\n", prevname  ? prevname  : "None"); 
	printf ("Next      : %s\n", nextname  ? nextname  : "None"); 
	printf ("Children  : %d\n", numChildren); 
	printf ("2nd child : %s\n", childnthname ? childnthname : "None"); 

	if (objname) mgFree (objname);
	if (parname) mgFree (parname);
	if (childname) mgFree (childname);
	if (prevname) mgFree (prevname);
	if (nextname) mgFree (nextname);
	if (childnthname) mgFree (childnthname);
}

static void PrintNodeName (mgrec* node)
{
	char* name = mgGetName (node);
	if (name) {
		printf ("   checking %s\n", name);
		mgFree (name);
	}
}

static mgrec* FindObjectBelow (mgrec* root, mgbool checkSiblings)
/* depth first, recursive function to find fltObject node at or below root */
{
	mgrec* object;
	mgrec* sibling;

	if (root == MG_NULL)
		return MG_NULL;

	/* echo this node's name as we examine it */
	PrintNodeName (root);

	/* if root node is an object, return it */
	if (mgIsCode (root, fltObject))
		return root;

	/* otherwise traverse to it's child (depth) */
	object = FindObjectBelow (mgGetChild (root), MG_TRUE);
	if (object != MG_NULL) return object;

	/* now check siblings if told to (breadth) 
		note: we will "loop" on siblings rather than "recurse" to avoid stack overflow.
		typically the "depth" of a hierarchy is shallow enough so recursion is ok for
		children, but since it is common for nodes to have thousands of siblings, 
		recursing on siblings might cause stack overflow.
		*/
	if (checkSiblings == MG_TRUE)
		sibling = mgGetNext (root);
	else
		sibling = MG_NULL;

	while (sibling != MG_NULL) 
	{
		object = FindObjectBelow (sibling, MG_FALSE);
		if (object != MG_NULL) return object;
		sibling = mgGetNext (sibling);
	}
	return MG_NULL;
}

int main (int argc, char* argv[])
{
	mgrec* db;
	mgrec* child;
	mgrec* object;
	char* filename;
	mgbool ok;

	/* check for correct number of arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <input_db_filename>\n", argv[0]);
		printf ("   Reads database: <input_db_filename>\n");
		printf ("   Manually traverse to find the first object node\n");  
		printf ("   If found, print the names of the object's relatives\n");
		printf ("   Auto traverse (mgWalk) the database; print all the nodes that are nested\n");
		printf ("   Print the file name associated with the object\n");
		printf ("\n");
		exit (EXIT_FAILURE);
	}

	/* initialize the OpenFlight API
		always call mgInit BEFORE any other OpenFlight API calls 
		*/
	mgInit (&argc, argv);

	/* open database */
   printf ("\nOpening database: %s\n", argv[1]);
	db = mgOpenDb (argv[1]);
	if (db == MG_NULL) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("%s\n", msgbuf);
		exit (EXIT_FAILURE);
	}

	/* make sure database has at least one child */
	child = mgGetChild (db);
	if (child == MG_NULL) {
		printf ("\nEmpty Database, no children found\n");
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}

	/* do a depth first recursive traversal of the database looking 
		for a normal object child */
	printf ("\nManually traversing database looking for object node:\n");
	object = FindObjectBelow (db, MG_FALSE);

	if (object == MG_NULL) {
		printf ("No (non-instanced) object node found in database\n");
		/* close the database file */
		mgCloseDb (db);
		exit (EXIT_FAILURE);
	}

	/* print names of the object record's parent, child, and next record */
	/* print how many children it has */
	/* print the name of the 2nd child */
	printf ("\nFound object:\n");
	PrintAdjacent (object);

	/* find the name of the database file from this object record */
	/* illustrates how you can get the database file name from any record */
	if ((filename = mgRec2Filename (object)) != MG_NULL) {
		printf ("Database file associated to object: %s\n", filename);
		mgFree (filename);
	}

	/* traverse database, look for records with nested children */
	printf ("\nAuto traversing (mgWalk) database looking for nested children:\n");
	mgWalk (db, FindNested, MG_NULL, MG_NULL, MWALK_NOREADONLY | MWALK_MASTER);

	/* close the database file */
	ok = mgWriteDb (db);
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all API function calls */
	mgExit ();
}
