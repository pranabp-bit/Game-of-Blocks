//blood bank management
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class blood_bank
{
private:
	string bname, baddress, bdname/*donor name*/;
	long long int bcontactno;
public:
	void enter() {   //Enter bank details
		cout << "Bank details:" << endl;
		cout << "Enter bank name:";
		cin >> (bname);
		cout << "Enter bank addresss:";
		cin >> (baddress);
		cout << "Enter bank's contact no.:";
		cin >> bcontactno;
		cout << "_______________________________________" << endl;
	}

	void display() { //display bank details
		cout << "Bank detials:" << endl;
		cout << "Bank name:" << bname << endl;
		cout << "Bank address:" << baddress << endl;
		cout << "Bank contact no:" << bcontactno << endl;
		cout << "_______________________________________" << endl;
	}

	string getdname() {  //return bank name
		return bname;
	}
};

class donor :public blood_bank {
private:
	string dname, bgroup, daddress;
	int donor_id, blood_donated;
	long long int dnumber;
public:
	void denter() {   //enter donor details
		enter();
		cout << "Donor details:" << endl;
		cout << "Enter donor name:";
		cin >> (dname);
		cout << "Enter donor id:";
		cin >> donor_id;
		cout << "Enter blood group:";
		cin >> bgroup;
		cout << "Enter address:";
		cin >> (daddress);
		cout << "Enter contact no:";
		cin >> dnumber;
		cout << "Enter the blood donated in ml:";
		cin >> blood_donated;
		cout << "_______________________________________" << endl;
	}

	void ddisplay() {         //display donor details
		display();
		cout << "Donor details:" << endl;
		cout << "Donor name:" << dname << endl;
		cout << "Donor id:" << donor_id << endl;
		cout << "Blood group:" << bgroup << endl;
		cout << "Address" << daddress << endl;
		cout << "Contact no:" << dnumber << endl;
		cout << "Blooddonated:" << blood_donated << endl;
		cout << "_______________________________________" << endl;
	}

	int getid() {    //return donor id
		return donor_id;
	}
	string getbgroup() {  //return donor blood group
		return bgroup;
	}
};


class patient :public blood_bank {
private:
	string pname, pgroup, pdisease;
	int p_id;
	long long pcontact;
public:
	void penter() {  //enter patient details
		enter();
		cout << "Patient details:" << endl;
		cout << "Enter patient name:";
		cin >> pname;
		cout << "Enter patient id:";
		cin >> p_id;
		cout << "Enter patient's blood group:";
		cin >> pgroup;
		cout << "Enter patient's reason for loss of blood:";
		cin >> pdisease;
		cout << "_______________________________________" << endl;
	}
	void pdisplay() {    //display patient details
		display();
		cout << "Patient details:" << endl;
		cout << "Patient name:" << pname << endl;
		cout << "Patient id:" << p_id << endl;
		cout << "Patient's blood group:" << pgroup << endl;
		cout << "patient's reason for loss of blood:" << pdisease << endl;
		cout << "_______________________________________" << endl;
	}
	int getp_id() {    //return patients details
		return p_id;
	}
	string getpgroup() {
		return pgroup;
	}
};

void writefiledonor(vector<donor>& dv, vector<patient>& pv)
{
	donor d;

	d.denter();
	dv.push_back(d);
}
void readfiledonor(vector<donor>& dv)
{
	for (int i = 0; i < dv.size(); i++)
	{
		dv[i].ddisplay();
	}
}
void readfilepatient(vector<patient>& pv)
{
	for (int i = 0; i < pv.size(); i++)
	{
		pv[i].pdisplay();
	}
}

void match(string agrp, vector<donor>& dv)//to find the blood group match of patient to donor
{
	patient p;
	donor d;
	int qty, cnt = 0, pos;
	for (int i = 0; i < dv.size(); i++)
	{
		if (strcasecmp(agrp.c_str(), (dv[i].getbgroup()).c_str()) == 0)
		{
			cnt = 1;
			cout << "Bloodmatch found!!" << endl;
		}
	}
	if (cnt == 0)
		cout << "Sorry..no match found :(" << endl;
}

void enter_patient_details(vector<donor>& dv, vector<patient>& pv)
{
	int a;
	string agrp; //bloodgrp for patient variable;
	patient p;

	p.penter();
	agrp = p.getpgroup();

	pv.push_back(p);
	cout << "Find the blood available in the blood bank?" << endl;
	cout << "Enter: 1:Yes. 2:No(exit)  :";
	cin >> a;
	switch (a)
	{
	case 1:match(agrp, dv); break;
	case 2:exit(0);
	}
}

void delete_patient_record(vector<donor>& dv, vector<patient>& pv)
{
	patient p;
	int no, flag = 0;
	cout << "Enter patient id to be deleted:";
	cin >> no;
	for (int i = 0; i < pv.size(); i++)
	{
		if (pv[i].getp_id() == no)
		{
			flag = 1;
			pv.erase(pv.begin() + i);
			cout << "Changes have been made." << endl;
		}
	}
	if (flag == 0)
	{
		cout << "No such record exists." << endl;
	}
	readfilepatient(pv);
}

void delete_donor_record(vector<donor>& dv, vector<patient>& pv)
{
	donor d;

	int no, flag = 0;

	cout << "Enter donor id no to be deleted:";
	cin >> no;
	for (int i = 0; i < dv.size(); i++)
	{
		if (dv[i].getid() == no)
		{
			flag = 1;
			dv.erase(dv.begin() + i);
			cout << "Changes have been made." << endl;
		}
	}
	if (flag == 0)
	{
		cout << "No such record exists." << endl;
	}

	readfiledonor(dv);

}

int main() {
	int menu;
	vector<donor> dv;
	vector<patient>pv;
	do {
		cout << "\n1.Enter records of donor.";
		cout << "\n2.Enter records of patient.";
		cout << "\n3.Delete the record of patients.";
		cout << "\n4.Delete the record of donor.";
		cout << "\n5.Exit:  ";
		cin >> menu;
		switch (menu)
		{
		case 1:writefiledonor(dv, pv);          //adds details of a new donor 
			break;
		case 2:enter_patient_details(dv, pv);   //adds details of a new patient, can check whether there is a donor with same blood group
			break;
		case 3:delete_patient_record(dv, pv);   //deletes details of patient with a given id, if found. displays the details of all remaining patients
			break;
		case 4:delete_donor_record(dv, pv);     //deletes details of donor with a given id, if found. displays the details of all remaining donors.
			break;
		case 5:exit(0);
			break;
		}
	} while (menu != 5);
	fflush(stdin);
	getchar();
	return 0;
}
/*
1.Enter records of donor.
2.Enter records of patient.
3.Delete the record of patients.
4.Delete the record of donor.
5.Exit:  1
Bank details:
Enter bank name:a
Enter bank addresss:a
Enter bank's contact no.:1
_______________________________________
Donor details:
Enter donor name:r
Enter donor id:12
Enter blood group:a+
Enter address:w
Enter contact no:1
Enter the blood donated in ml:1
_______________________________________
1.Enter records of donor.
2.Enter records of patient.
3.Delete the record of patients.
4.Delete the record of donor.
5.Exit:  1
Bank details:
Enter bank name:dd
Enter bank addresss:f
Enter bank's contact no.:2
_______________________________________
Donor details:
Enter donor name:w
Enter donor id:33
Enter blood group:b+
Enter address:qw
Enter contact no:2
Enter the blood donated in ml:12
_______________________________________
1.Enter records of donor.
2.Enter records of patient.
3.Delete the record of patients.
4.Delete the record of donor.
5.Exit:  2
Bank details:
Enter bank name:r
Enter bank addresss:w
Enter bank's contact no.:4
_______________________________________
Patient details:
Enter patient name:p
Enter patient id:26
Enter patient's blood group:A+
Enter patient's reason for loss of blood:potty
_______________________________________
Find the blood available in the blood bank?
Enter: 1:Yes. 2:No(exit)  :1
Sorry..no match found :(
1.Enter records of donor.
2.Enter records of patient.
3.Delete the record of patients.
4.Delete the record of donor.
5.Exit:  3
Enter patient id to be deleted:2
No such record exists.
Bank detials:
Bank name:r
Bank address:w
Bank contact no:4
_______________________________________
Patient details:
Patient name:p
Patient id:26
Patient's blood group:Ab
patient's reason for loss of blood:potty
_______________________________________
1.Enter records of donor.
2.Enter records of patient.
3.Delete the record of patients.
4.Delete the record of donor.
5.Exit:  2
Bank details:
Enter bank name:t
Enter bank addresss:t
Enter bank's contact no.:43
_______________________________________
Patient details:
Enter patient name:y
Enter patient id:69
Enter patient's blood group:A+
Enter patient's reason for loss of blood:ss
_______________________________________
Find the blood available in the blood bank?
Enter: 1:Yes. 2:No(exit)  :1
Bloodmatch found!!
1.Enter records of donor.
2.Enter records of patient.
3.Delete the record of patients.
4.Delete the record of donor.
5.Exit:  3
Enter patient id to be deleted:26
Changes have been made.
Bank detials:
Bank name:t
Bank address:t
Bank contact no:43
_______________________________________
Patient details:
Patient name:y
Patient id:69
Patient's blood group:A+
patient's reason for loss of blood:ss
_______________________________________
1.Enter records of donor.
2.Enter records of patient.
3.Delete the record of patients.
4.Delete the record of donor.
5.Exit:  4
Enter donor id no to be deleted:56
No such record exists.
Bank detials:
Bank name:a
Bank address:a
Bank contact no:1
_______________________________________
Donor details:
Donor name:r
Donor id:12
Blood group:a+
Addressw
Contact no:1
Blooddonated:1
_______________________________________
Bank detials:
Bank name:dd
Bank address:f
Bank contact no:2
_______________________________________
Donor details:
Donor name:w
Donor id:33
Blood group:b+
Addressqw
Contact no:2
Blooddonated:12
_______________________________________
1.Enter records of donor.
2.Enter records of patient.
3.Delete the record of patients.
4.Delete the record of donor.
5.Exit:  4
Enter donor id no to be deleted:12
Changes have been made.
Bank detials:
Bank name:dd
Bank address:f
Bank contact no:2
_______________________________________
Donor details:
Donor name:w
Donor id:33
Blood group:b+
Addressqw
Contact no:2
Blooddonated:12
_______________________________________
1.Enter records of donor.
2.Enter records of patient.
3.Delete the record of patients.
4.Delete the record of donor.
5.Exit:  5
*/
