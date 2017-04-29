#include "ClubMember.h"
#include "Link.h"




Link::Link(Link *prev, Link *next, ClubMember *player){
	pPrev       = prev;
	pNext       = next;
	pClubMember = player;
}




Link::~Link(){
	delete pClubMember;
}
