#include "CcaseFileSystem.h"

void CcaseFileSystem::changeFiles(int input) {

	switch (input) {
	case '1':
		currentView = CFSView::DOCUMENT;
		break;
	case '2':
		currentView = CFSView::EVIDENCE;
		break;
	case '3':
		currentView = CFSView::SUSPECT;
		break;
	case 77:
		if (currentView == CFSView::EVIDENCE) {
			if (currentEvidenceFiles < (int)discoveredEvidence.size() - 1) currentEvidenceFiles++;
		}
		else if (currentView == CFSView::SUSPECT) {
			if (currentSuspectFiles < (int)discoveredSuspect.size() - 1) currentSuspectFiles++;
		}
		else if (currentView == CFSView::DOCUMENT) {
			if (currentFiles < (int)discoveredDocument.size() - 1) currentFiles++;
		}
		break;
	case 75:
		if (currentView == CFSView::EVIDENCE) {
			if (currentEvidenceFiles > 0) currentEvidenceFiles--;
		}
		else if (currentView == CFSView::SUSPECT) {
			if (currentSuspectFiles > 0) currentSuspectFiles--;
		}
		else if (currentView == CFSView::DOCUMENT) {
			if (currentFiles > 0) currentFiles--;
		}
		break;
	}

	
}

void CcaseFileSystem::addDocument()
{
	discoveredDocument = {
		"AUTOPSY REPORT\n"
		"Case No: WC-0417\n"
		"Examiner: Willow's Creek County Forensics\n\n"
		"Cause of Death: Blunt force trauma to the back of the skull.\n"
		"Time of Death: Estimated between 17:30 and 18:15, Thursday.\n\n"
		"Findings:\n"
		"A single deep wound at the base of the skull, consistent with a\n"
		"heavy, rounded object. Wound depth and bruising pattern suggest\n"
		"a single forceful blow rather than a prolonged struggle.\n"
		"Minor defensive bruising found on the victim's left forearm.\n"
		"Trace blood residue recovered separately at the scene is\n"
		"being cross-matched against the wound.\n\n"
		"Toxicology: Pending.",

		"CASE DETAILS\n"
		"Case No: WC-0417\n"
		"Location: Smith Residence, Willow's Creek\n\n"
		"Reported: Thursday, 18:34 - Call received by Det. Black via\n"
		"Det. Angelo Batista.\n"
		"Scene Secured: Thursday, ~19:10 - Officers cordon off premises.\n"
		"Body Discovered In: Study Room, ground floor.\n"
		"Estimated Time of Death: Between 17:30 and 18:15, Thursday.\n\n"
		"Persons with contact near time of death:\n"
		"  - Emily Smith (Wife) - claims to have been upstairs reading.\n"
		"  - Michael Turner (Business Partner) - claims he left at 16:15pm.\n"
		"  - Trisha Lopez (Maid) - present in residence.\n"
		"  - Sarah Collins (Neighbour) - claims to have been home alone.\n\n"
		"No signs of forced entry found at doors or windows.\n"
		"Evidence recovered from study room: broken whiskey glass, brass\n"
		"candlestick with blood residue, faint gunpowder trace.",

		"VICTIM DESCRIPTION\n\n"
		"Name: Jonathan Smith\n"
		"Age: 52\n"
		"Occupation: CEO, Smith Holdings\n"
		"Residence: Willow's Creek Mansion\n\n"
		"Known Associates: Emily Smith (wife), Michael Turner (business\n"
		"partner / co-founder), Sarah Collins (neighbour).\n\n"
		"Notes: A wealthy businessman and owner of the mansion.\n"
		"reserved and composed, he keeps to himself\n"
		"often seeming preoccupied even when his wife tries to get his attention.\n"
	};
}

void CcaseFileSystem::addDescription(string words)
{
	evidenceDescription = words;
}


void CcaseFileSystem::renderFiles() {

	switch (currentView) {
	case CFSView::EVIDENCE:
		renderEvidenceFiles();
		return;
		break;
	case CFSView::SUSPECT:
		renderSuspectFiles();
		return;
		break;
	case CFSView::DOCUMENT:
		break;
	}

	CUI::GetInstance().Clear();
	if (discoveredDocument.empty()) {

		cout << "#=============================#" << endl << endl;
		cout << "No documents added yet" << endl << endl;
		cout << "#=============================#";

	}
	else
	{
		cout << "             " << currentFiles + 1 << " / " << discoveredDocument.size() << endl;
		cout << "#=============================#" << endl;
		cout << discoveredDocument[currentFiles] << endl << endl << "Description:" << endl; //still need getDoc func here for push
		cout << "#=============================#";
	}
	
}

void CcaseFileSystem::renderEvidenceFiles() {
	CUI::GetInstance().Clear();
	if (discoveredEvidence.empty()) {

		cout << "#=============================#" << endl << endl;
		cout << "No evidences collected yet" << endl << endl;
		cout << "#=============================#";

	}
	else
	{
		cout << "             " << currentEvidenceFiles + 1 << " / " << discoveredEvidence.size() << endl;
		cout << "#=============================#" << endl;
		cout << discoveredEvidence[currentEvidenceFiles].GetName() << endl << endl
			<< "Description:" + discoveredEvidence[currentEvidenceFiles].GetDescription() << endl;
		cout << "#=============================#";
	}
}

void CcaseFileSystem::renderSuspectFiles()
{
	CUI::GetInstance().Clear();
	if (discoveredSuspect.empty()) {
		cout << "#=============================#" << endl << endl;
		cout << "No suspect yet" << endl << endl;
		cout << "#=============================#";
	}
	else
	{
		cout << "             " << currentSuspectFiles + 1 << " / " << discoveredSuspect.size() << endl;
		cout << "#=============================#" << endl;
		cout << discoveredSuspect[currentSuspectFiles].getName() << endl;
		cout << "Age: " << discoveredSuspect[currentSuspectFiles].getAge() << endl;
		cout << "Occupation: " << discoveredSuspect[currentSuspectFiles].getOccupation() << endl;
		//cout << "Description: " << endl;
		cout << "#=============================#";
	}
}

void CcaseFileSystem::addEvidence(CEvidence::Evidence type)
{
	for (CEvidence& e : discoveredEvidence) {
		if (e.getEvidence() == type) {
			return;
		}
	}
	CEvidence e;
	e.SetEvidence(type);
	e.SetFound(true);
	discoveredEvidence.push_back(e);

}

void CcaseFileSystem::addSuspect(NPC::People name)
{
	for (NPC& p : discoveredSuspect) {
		if (p.getPerson() == name) {
			return;
		}
	}
	NPC p;
	p.setPerson(name);
	discoveredSuspect.push_back(p);
}


void CcaseFileSystem::showFiles(char input) {
	if (input == 'c') {
		isCFSOpen = !isCFSOpen;
	}
	if (isCFSOpen) {
		renderFiles();
	}
}

bool CcaseFileSystem::getCFSState() {
	return isCFSOpen;
}

//void CcaseFileSystem::addNotes() {
//	CUI::GetInstance().Clear();
//	string notesText;
//	cout << "What's on your mind, Mr Black?: ";
//	getline(cin, notesText);
//	notes[currentSuspectFiles][currentNotes[currentSuspectFiles]] = notesText;
//	currentNotes[currentSuspectFiles]++;
//	renderSuspectFiles();
//	
//}

CcaseFileSystem::CcaseFileSystem() {
	addDocument();
}