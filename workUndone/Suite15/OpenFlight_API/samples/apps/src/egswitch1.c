/*******************************************************************************

   Sample file: EGSWITCH1.C

   Objectives: 
		Manipulate switch node masks

   Program functions: 
      Add Switch Node Masks
      Get and Set bits in the masks
   
   API functions used: 
      mgInitSwitchMask(), mgAddSwitchMask(),
      mgSetSwitchBit(), mgGetSwitchBit(),
      mgGetSwitchMaskCount(), mgGetSwitchMaskNo(),
		mgNewRec(), mgAttach(),
		mgNewDb(), mgWriteDb(), mgCloseDb()
   
*******************************************************************************/

#include <stdlib.h>
#include <stdio.h>

/* include all OpenFlight API headers */
#include <mgapiall.h>

static void BuildSwitchMasks (mgrec* switchRec)
/* build a set of switch masks, each one that turns on a 
	single child of the switch node */
{
	int i, switchNo;
	mgbool ok;
	int numChildren = mgCountChild (switchRec);

	/* create a set of new masks, each one turns on a 
		single child of the switch node */

	for (i = 0; i < numChildren; i++) 
	{
		/* create a new mask that will turn on this child */
		switchNo = mgAddSwitchMask (switchRec);

		/* init all bits of this mask to off */
		ok = mgInitSwitchMask (switchRec, switchNo, MG_FALSE);

		/* then turn on the bit corresponding to this child */
		ok = mgSetSwitchBit (switchRec, switchNo, i, MG_TRUE);
	}
}

static void PrintSwitchMasks (mgrec* switchRec)
/* print the values of each of the bits of each of the
	switch masks of the switch node */
{
	int maskCount, curMaskNo;
	int maskNo, bitNo;
	mgbool ok, onFlag;

	/* Get number of masks defined for the switch node */
	maskCount = mgGetSwitchMaskCount (switchRec);

	/* Get the current switch mask number (info only) */
	ok = mgGetSwitchMaskNo (switchRec, &curMaskNo);

	/* Get the values for each bit of the mask and print it */
	for (maskNo = 0; maskNo < maskCount; maskNo++)
	{
		bitNo = 0;	/* bitnum represents the bit number */
		mgSendMessage (MMSG_STATUS, "Mask %d :", maskNo);
		while (mgGetSwitchBit (switchRec, maskNo, bitNo, &onFlag))
		{
			mgSendMessage (MMSG_STATUS, "\tbit %d : %d", bitNo, onFlag);
			bitNo++;
		}
	}
}

#define REPORT_NODE_CREATED(_node)\
	printf ("Creating " #_node " : %s\n", ((_node)!=MG_NULL) ? "Ok" : "Failed");

#define REPORT_NODE_ATTACHED(_ok,_parent,_child)\
	printf ("Attaching " #_child " to " #_parent " : %s\n", ((_ok)==MG_TRUE) ? "Ok" : "Failed");

int main (int argc, char* argv[])
{
	mgrec* db;
	mgrec* group;
	mgrec* switchRec;
	mgrec* object1;
	mgrec* object2;
	mgrec* object3;
	mgbool ok;

	/* check for correct number of arguments */
	if (argc < 2) {
		printf ("\nUsage: %s <create_db_filename>\n", argv[0]);
		printf ("   Creates database: <create_db_filename>\n");
		printf ("   Creates switch node with masks\n");
		printf ("   Get and set bits in the masks\n");
		printf ("\n");
		exit (EXIT_FAILURE);
	}

	/* initialize the OpenFlight API
		always call mgInit BEFORE any other OpenFlight API calls 
		*/
	mgInit (&argc, argv);

	/* start a new OpenFlight database, overwrite if exists */
	mgSetNewOverwriteFlag (MG_TRUE);
   printf ("\nCreating database: %s\n", argv[1]);
	db = mgNewDb (argv[1]);
	if (db == MG_NULL) {
		char msgbuf [1024];
		mgGetLastError (msgbuf, 1024);
		printf ("%s\n", msgbuf);
		mgExit ();
		exit (EXIT_FAILURE);
	}

	/* Throughout the following, error conditions are checked for
		and (in some cases) reported but processing will continue.  
		In your code, you should consider appropriate action upon 
		function failures.
		*/

	/* create group, switch, and 3 object nodes */
	group = mgNewRec (fltGroup);				REPORT_NODE_CREATED (group);
	ok = mgAttach (db, group);					REPORT_NODE_ATTACHED (ok, db, group);

	switchRec = mgNewRec (fltSwitch);		REPORT_NODE_CREATED (switchRec);
	ok = mgAttach (group, switchRec);		REPORT_NODE_ATTACHED (ok, group, switchRec);

	object1 = mgNewRec (fltObject);			REPORT_NODE_CREATED (object1);
	object2 = mgNewRec (fltObject);			REPORT_NODE_CREATED (object2);
	object3 = mgNewRec (fltObject);			REPORT_NODE_CREATED (object3);
	
	ok = mgAttach (switchRec, object1);		REPORT_NODE_ATTACHED (ok, switchRec, object1);
	ok = mgAttach (switchRec, object2);		REPORT_NODE_ATTACHED (ok, switchRec, object2);
	ok = mgAttach (switchRec, object3);		REPORT_NODE_ATTACHED (ok, switchRec, object3);

	/* set up the switch masks */
	BuildSwitchMasks (switchRec);

	/* echo the values of the switch masks */
	PrintSwitchMasks (switchRec);

	/* write the database */
	ok = mgWriteDb (db);
	if (ok == MG_FALSE)
		printf ("Error writing database\n");
	
	/* close the database */
	ok = mgCloseDb (db);
	if (ok == MG_FALSE)
		printf ("Error closing database\n");

	/* always call mgExit() AFTER all OpenFlight API calls */
	mgExit ();

   exit (0);
}


