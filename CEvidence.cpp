#include "CEvidence.h"

void CEvidence::SetEvidence(Evidence E){
	//type = E;

	switch (E) {
	case Brass_Candlestick:
		name = "Brass Candlestick";
		Dialogue[0] = "'Hmm, what's this? Looks like blood' Black mutters";
		Dialogue[1] = "At the base of a brass candlestick, a blood smudge can be seen.";
		Dialogue[2] = "Seems like it was wiped carelessly, as if in a rush";
		Dialogue[3] = "Detective Black places the candlestick into a Ziploc bag";
		description = "A heavy brass candlestick, roughly a foot tall, recovered from the "
			"study room shelf. The base carries a faint reddish-brown smudge, "
			"hastily wiped rather than cleaned - the kind of mark left behind by "
			"someone in a hurry, not someone trying to be thorough. The weight and "
			"shape of the base line up uncomfortably well with the wound described "
			"in the autopsy report. No fingerprints are visible on the surface.";
		length = 4;
		id = 3001;
		found = false;
		break;
	case Broken_Whiskey_Glass:  //Change dialogue to all evidence
		name = "Broken Whiskey Glass";
		Dialogue[0] = "As Detective Black looks closely at the Broken Whiskey Glass on the floor...";
		Dialogue[1] = "he could see a fingerprint smudge";
		Dialogue[2] = "He put the Broken Whiskey Glass into a Ziploc Bag";
		description = "A shattered crystal whiskey glass, found near the body, its base "
			"still intact. A partial fingerprint is smudged along one of the larger "
			"fragments, preserved just well enough to be lifted. A faint amber "
			"residue clings to the inside - whiskey, left to dry rather than spilled "
			"and cleaned. Whoever was drinking from this glass either left in a "
			"hurry, or never got the chance to finish.";
		length = 3;
		id = 3002;
		found = false;
		break;
	case Gunpowder_Ziploc:
		name = "Gunpowder Ziploc";
		Dialogue[0] = "'Has any officer been in here holding a pistol' asks Black";
		Dialogue[1] = "'No hermano,  just me and the forensics' said Batista";
		Dialogue[2] = "'Funny, there seems to be a gunpowder trace here...' Black Scoffs";
		Dialogue[3] = "Detective Black places the gunpowder into a Ziploc bag";
		description = "A small sample of fine grey residue, lifted from a patch of carpet "
			"near the study room window. Unmistakably gunpowder, though there is no "
			"gunshot wound on the body and no firearm recovered anywhere on the "
			"premises. Curious, given the cause of death was blunt trauma - if a "
			"weapon was fired in this room, it either missed entirely, or was never "
			"meant for the victim at all.";
		length = 4;
		id = 3003;
		found = false;
		break;
	case Suspicious_Glove:
		name = "Suspicious Glove";
		description = "A single leather glove, found tucked behind a cushion, clearly out "
			"of place. The stitching is fine - not cheap work - and the size "
			"suggests a man's hand. Dark stains mar the fingertips, dried stiff "
			"into the leather. There's no matching glove anywhere nearby, which "
			"raises the question of where its pair ended up, and why only one was "
			"left behind.";
		length = 0;
		id = 3004;
		found = false;
		break;
	case BrokenWhiskey_Glass_Report:
		name = "BrokenWhiskey Glass Report";
		description = "Forensics' written analysis of the partial print lifted from the "
			"broken whiskey glass. After running it through the system, the report "
			"confirms a clean match to Mr. Turner's prints on file, taken during an "
			"earlier, unrelated background check. The report notes the print is "
			"recent - laid down within the last day or so, not an old residue from "
			"a previous visit.";
		length = 0;
		id = 3005;
		found = false;
		break;
	case Brass_Candlestick_Report:
		name = "Brass Candlestick Report";
		description = "Lab results on the blood smudge recovered from the base of the "
			"brass candlestick. The sample has been matched to Mr. Smith - the "
			"victim himself. The report notes the blood was deposited by contact, "
			"not spatter, which is consistent with the candlestick having struck "
			"him directly. Combined with the autopsy, this places the candlestick "
			"firmly among the likely murder weapons.";
		length = 0;
		id = 3006;
		found = false;
		break;
	case Suspicious_Glove_Report:
		name = "Suspicious Glove Report";
		description = "A forensic breakdown of the suspicious glove recovered from the "
			"living room. The dried stains on the fingertips have been confirmed "
			"as blood belonging to Mr. Smith. More unexpectedly, trace strands of "
			"body hair caught in the seams have been matched to Mr. Turner. Two "
			"people's evidence, one glove - either it was shared, planted, or "
			"someone's story is missing a piece.";
		length = 0;
		id = 3007;
		found = false;
		break;
	case Picture_of_Muddy_shoeprint:
		name = "Picture of Muddy shoeprint";
		Dialogue[0] = "'Check this out. It’s mud, isn't it?' questioned Black";
		Dialogue[1] = "Yeah. And from the looks of it...";
		Dialogue[2] = "'it seems to be a shoe print coming from the back door, through the garden' replied Silas";
		Dialogue[3] = "'Take a picture of this, Silas; this could be our murderer' said Mr Black";
		Dialogue[4] = " (The Image of the muddy shoe print has been added to your evidence inventory)";
		description = "A photograph of a muddy shoeprint tracked in from the garden, leading "
			"toward the back door of the mansion. The print is a men's dress shoe, "
			"mid-to-large size, and still fresh enough at the time of the photo to "
			"suggest it was made the same evening as the murder, not days before. "
			"Whoever left it either entered or left the property through the "
			"garden - a route none of the suspects have mentioned using.";
		length = 5;
		id = 3008;
		found = false;
		break;
	case Shoebox_of_property_Photos:
		name = "Shoebox of Property Photos";
		Dialogue[0] = "Detective Black spots a shoebox under the coffee table...";
		Dialogue[1] = "-EVIDENCE- scrawled across a strip of tape on the lid.";
		Dialogue[2] = "'Evidence?' Black mutters.";
		Dialogue[3] = "He lifts the lid. Inside: a stack of photographs: ";
		Dialogue[4] = "a garden hose laid out across the grass, an apple tree leaning over the fence line...";
		Dialogue[5] = "gardening rake tipped over the boundary, more in the same vein. Dozens of them, some yellowed with age.";
		Dialogue[6] = "'What are these?' Black asks, flipping through the pile";
		Dialogue[7] = "Silas walks over, glancing down. 'Looks like evidence for a property feud'";
		Dialogue[8] = "'That might be motive' Black says.";
		description = "A shoebox stuffed with photographs documenting a long-running "
			"property dispute - fence lines, overhanging trees, tools left on the "
			"wrong side of a boundary. Some photos are recent, others yellowed with "
			"age, suggesting the feud has simmered for years rather than months. "
			"The word 'EVIDENCE' scrawled across the lid implies someone was "
			"building a case of their own, long before Mr. Smith ever ended up "
			"dead.";
		length = 9;
		id = 3009;
		found = false;
		break;
	case Bank_Statement:
		name = "Bank Statement";
		Dialogue[0] = "Silas! Found something - Black calls, beckoning him over.";
		Dialogue[1] = "Silas leans in. Black holds up a folded bank statement...";
		Dialogue[2] = "several transactions circled in pen — presumably Jonathan's own hand";
		Dialogue[3] = "Withdrawals.Big ones.Same amount, every few weeks, going back months - Black says.";
		Dialogue[4] = "Any idea where it's going - Silas asks.";
		Dialogue[5] = "Not yet.No memo, no transfer name — just cash pulled out, over and over - Black flips the page...";
		Dialogue[6] = "while frowning - Man's bleeding money from somewhere, and he didn't want a paper trail explaining why.";
		Dialogue[7] = "He tucks the statement into an evidence bag - We'll need to find out who's on the other end of this.";
		Dialogue[8] = "(Bank Statement added to your evidence inventory.)";
		description = "A folded bank statement pulled from Jonathan Smith's own study, "
			"several withdrawals circled by hand - presumably his own. The "
			"transactions follow a pattern: large, round sums, pulled out every few "
			"weeks over the course of months. No memo, no named recipient, no "
			"digital transfer trail - just cash, repeatedly, and deliberately "
			"untraceable. Whatever Jonathan was funding, he didn't want a record "
			"of who it was going to.";
		length = 9;
		id = 3010;
		found = false;
		break;
	case Divorce_Papers:
		name = "Divorce Papers";
		Dialogue[0] = "Silas looks inside the nightstand's drawer";
		Dialogue[1] = "Eh, just a bunch of cosmetics - he mutters.";
		Dialogue[2] = "He reaches in to feel around. His hand brushes against something foreign...";
		Dialogue[3] = "taped to	the underside of the drawer above. He pulls out what seems to be an Envelope.";
		Dialogue[4] = "Found something, Black. - said Silas";
		Dialogue[5] = "Black opens it and finds an unsigned, unfiled divorce filing with Emily listed as the petitioner.";
		Dialogue[6] = "She was planning to leave him - Silas says.";
		Dialogue[7] = "Looks like it - Black replies - But why didn't she file?";
		Dialogue[8] = "(Divorce Papers added to your evidence inventory.)";
		description = "An unsigned, unfiled divorce petition, found taped to the underside "
			"of a nightstand drawer - deliberately hidden, not simply misplaced. "
			"Emily Smith is listed as the petitioner. The paperwork appears "
			"complete and ready to be filed, yet never was. Whatever stopped her "
			"from following through, the papers suggest she had already made up "
			"her mind to leave her husband well before the night he died.";
		length = 9;
		id = 3011;
		found = false;
		break;

	}
}

CEvidence::Evidence CEvidence::getEvidence()
{
	return type;
}

string CEvidence::GetDialogue(int num)
{
	return string(Dialogue[num]);
}

void CEvidence::placeEvidence(int x, int y){
	SetPosX(x);
	SetPosY(y);
}

bool CEvidence::GetFound(){
	return found;
}

void CEvidence::SetFound(bool find){
	found = find;
}

void CEvidence::SetName(string namegive){
	name = namegive;
}

string CEvidence::GetName(){
	return string(name);
}

int CEvidence::GetDialogueLength()
{
	length = sizeof(Dialogue);

	return length;
}

int CEvidence::GetLength(){
	return length;
}

CEvidence::CEvidence(string Name){
	name = Name;
	found = false;
	type = Brass_Candlestick;
}

int CEvidence::GetId()
{
	return id;
}

string CEvidence::GetDescription()
{
	return string(description);
}


CEvidence::CEvidence()
{
	found = false;
	type = Brass_Candlestick;
}
