#include "cell.h"



cell::cell()
{
}


cell::~cell()
{
}

bool cell::sphcoltest() {
	if (spcell.size() > 1) {
		for (auto & s : spcell) {
			for (auto & l : spcell) {
				if (s == l) {
					continue;
				}
				else {
					glm::vec3 d = s->getPos() - l->getPos();
					float dist2 = glm::dot(d, d);
					float radSum = s->getradius() + l->getradius();
					
					if (dist2 <= radSum * radSum) { 
						glm::vec3 di = s->getPos() - l->getPos();
						float dist2i = glm::dot(di, di);
						float difference = 2.0f*s->getradius() - dist2;
						glm::vec3 anorm = l->getPos() - s->getPos();
						anorm = glm::normalize(anorm);
						s->setPos(s->getPos() + (difference * anorm)/2.0f);
						l->setPos(l->getPos() - (difference * anorm)/2.0f);
						float s1 = glm::dot(s->getVel(), anorm);
						float s2 = glm::dot(l->getVel(), anorm);
						float op = (2.0f*(s1 - s2)) / (s->getMass() + l->getMass());
						glm::vec3 newvel1 = s->getVel() - op * l->getMass() * anorm;
						glm::vec3 newvel2 = l->getVel() + op * s->getMass() * anorm;
						s->setVel(newvel1);
						l->setVel(newvel2);

						return dist2 <= radSum * radSum;
					}

					
				}
			}
		}
	}
}