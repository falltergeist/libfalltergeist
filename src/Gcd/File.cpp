/*
 * Copyright 2012-2015 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// C++ standard includes

// libfalltergeist includes
#include "../Gcd/File.h"
#include "../Exception.h"

// Third party includes

namespace libfalltergeist
{
namespace Gcd
{

File::File(Dat::Entry* datFileEntry) : Dat::Item(datFileEntry)
{
    _initialize();
}

File::File(std::ifstream * stream) : Dat::Item(stream)
{
    _initialize();
}

File::~File()
{
}

void File::_initialize()
{
    if (_initialized) return;
    Dat::Item::_initialize();
    Dat::Item::setPosition(0);

    unsigned int uint32;

    // unknown 1
    *this >> _unknown1;

    // primary stats
    for (unsigned int i = STATS_STRENGTH; i <= STATS_LUCK; i++)
    {
        *this >> uint32;
        setStat(i, uint32);
    }

    // secondary stats
    *this >> _hitPoints >> _actionPoints >> _armorClass;

    // unknown 2
    *this >> _unknown2;

    *this >> _meleeDamage >> _carryWeight >> _sequence >> _healingRate >> _criticalChance >> _criticalHitModifier;

    for (unsigned int i = DAMAGE_NORMAL; i <= DAMAGE_EXPLOSIVE; i++)
    {
        *this >> uint32;
        setDamage(i, uint32);
    }
    for (unsigned int i = DAMAGE_NORMAL; i <= DAMAGE_EXPLOSIVE; i++)
    {
        *this >> uint32;
        setResistance(i, uint32);
    }

    *this >> _radiationResistance >> _poisonResistance >> _age >> _gender;

    // bonuses to primary stats
    for (unsigned int i = STATS_STRENGTH; i <= STATS_LUCK; i++)
    {
        *this >> uint32;
        setStatBonus(i, uint32);
    }

    // bonuses to secondary stats
    *this >> _hitPointsBonus >> _actionPointsBonus >> _armorClassBonus;

    // unknown 3
    *this >> _unknown3;

    *this   >> _meleeDamageBonus >> _carryWeightBonus >> _sequenceBonus >> _healingRateBonus
            >> _criticalChanceBonus >> _criticalHitModifierBonus;
    for (unsigned int i = DAMAGE_NORMAL; i <= DAMAGE_EXPLOSIVE; i++)
    {
        *this >> uint32;
        setDamageBonus(i, uint32);
    }
    for (unsigned int i = DAMAGE_NORMAL; i <= DAMAGE_EXPLOSIVE; i++)
    {
        *this >> uint32;
        setResistanceBonus(i, uint32);
    }
    *this >> _radiationResistanceBonus >> _poisonResistanceBonus >> _ageBonus >> _genderBonus;

    //skills
    for (unsigned int i = SKILLS_1; i <= SKILLS_18; i++)
    {
        *this >> uint32;
        setSkill(i, uint32);
    }

    // unknown
    *this >> _unknown4 >> _unknown5 >> _unknown6 >> _unknown7;

    // name
    char * name = new char[32]();
    this->readBytes(name, 32);
    setName(name);
    delete [] name;

    *this   >> _firstTaggedSkill
            >> _secondTaggedSkill
            >> _thirdTaggedSkill
            >> _fourthTaggedSkill
            >> _firstTrait
            >> _secondTrait
            >> _characterPoints;
}

unsigned int File::stat(unsigned int number)
{
    if (number > 6) throw Exception("File::stat() - number out of range: " + std::to_string(number));
    _initialize();
    return _stats.at(number);
}

void File::setStat(unsigned int number, unsigned int value)
{
    if (number > 6) throw Exception("File::setStat() - number out of range: " + std::to_string(number));
    _stats.at(number) = value;
}

unsigned int File::statBonus(unsigned int number)
{
    if (number > 6) throw Exception("File::statBonus() - number out of range: " + std::to_string(number));
    _initialize();
    return _statsBonus.at(number);
}

void File::setStatBonus(unsigned int number, unsigned int value)
{
    if (number > 6) throw Exception("File::setStatBonus() - number out of range: " + std::to_string(number));
    _statsBonus.at(number) = value;
}

unsigned int File::skill(unsigned int number)
{
    if (number > 17) throw Exception("File::skill() - number out of range: " + std::to_string(number));
    _initialize();
    return _skills.at(number);
}

void File::setSkill(unsigned int number, unsigned int value)
{
    if (number > 17) throw Exception("File::setSkill() - number out of range: " + std::to_string(number));
    _skills.at(number) = value;
}

unsigned int File::damage(unsigned int type)
{
    if (type > 6) throw Exception("File::damage() - type out of range: " + std::to_string(type));
    _initialize();
    return _damage.at(type);
}

void File::setDamage(unsigned int type, unsigned int value)
{
    if (type > 6) throw Exception("File::setDamage() - type out of range: " + std::to_string(type));
    _damage.at(type) = value;
}

unsigned int File::damageBonus(unsigned int type)
{
    if (type > 6) throw Exception("File::damageBonus() - type out of range: " + std::to_string(type));
    _initialize();
    return _damageBonus.at(type);
}

void File::setDamageBonus(unsigned int type, unsigned int value)
{
    if (type > 6) throw Exception("File::setDamageBonus() - type out of range: " + std::to_string(type));
    _damageBonus.at(type) = value;
}

unsigned int File::resistance(unsigned int type)
{
    if (type > 6) throw Exception("File::resistance() - type out of range: " + std::to_string(type));
    _initialize();
    return _resistance.at(type);
}

void File::setResistance(unsigned int type, unsigned int value)
{
    if (type > 6) throw Exception("File::setResistance() - type out of range: " + std::to_string(type));
    _resistance.at(type) = value;
}

unsigned int File::resistanceBonus(unsigned int type)
{
    if (type > 6) throw Exception("File::resistanceBonus() - type out of range: " + std::to_string(type));
    _initialize();
    return _resistanceBonus.at(type);
}

void File::setResistanceBonus(unsigned int type, unsigned int value)
{
    if (type > 6) throw Exception("File::setResistanceBonus() - type out of range: " + std::to_string(type));
    _resistanceBonus.at(type) = value;
}

void File::setHitPoints(unsigned int hitPoints)
{
    _hitPoints = hitPoints;
}

unsigned int File::hitPoints()
{
    _initialize();
    return _hitPoints;
}

void File::setActionPoints(unsigned int actionPoints)
{
    _actionPoints = actionPoints;
}

unsigned int File::actionPoints()
{
    _initialize();
    return _actionPoints;
}

void File::setArmorClass(unsigned int armorClass)
{
    _armorClass = armorClass;
}

unsigned int File::armorClass()
{
    _initialize();
    return _armorClass;
}

void File::setMeleeDamage(unsigned int meleeDamage)
{
    _meleeDamage = meleeDamage;
}

unsigned int File::meleeDamage()
{
    _initialize();
    return _meleeDamage;
}

void File::setCarryWeight(unsigned int carryWeight)
{
    _carryWeight = carryWeight;
}

unsigned int File::carryWeight()
{
    _initialize();
    return _carryWeight;
}

void File::setSequence(unsigned int sequence)
{
    _sequence = sequence;
}

unsigned int File::sequence()
{
    _initialize();
    return _sequence;
}

void File::setHealingRate(unsigned int healingRate)
{
    _healingRate = healingRate;
}

unsigned int File::healingRate()
{
    _initialize();
    return _healingRate;
}

void File::setCriticalChance(unsigned int criticalChance)
{
    _criticalChance = criticalChance;
}

unsigned int File::criticalChance()
{
    _initialize();
    return _criticalChance;
}

void File::setCriticalHitModifier(unsigned int criticalHitModifier)
{
    _criticalHitModifier = criticalHitModifier;
}

unsigned int File::criticalHitModifier()
{
    _initialize();
    return _criticalHitModifier;
}

void File::setRadiationResistance(unsigned int radiationResistance)
{
    _radiationResistance = radiationResistance;
}

unsigned int File::radiationResistance()
{
    _initialize();
    return _radiationResistance;
}

void File::setPoisonResistance(unsigned int poisonResistance)
{
    _poisonResistance = poisonResistance;
}

unsigned int File::poisonResistance()
{
    _initialize();
    return _poisonResistance;
}

void File::setAge(unsigned int age)
{
    _age = age;
}

unsigned int File::age()
{
    _initialize();
    return _age;
}

void File::setGender(unsigned int gender)
{
    _gender = gender;
}

unsigned int File::gender()
{
    _initialize();
    return _gender;
}

void File::setHitPointsBonus(unsigned int hitPointsBonus)
{
    _hitPointsBonus = hitPointsBonus;
}

unsigned int File::hitPointsBonus()
{
    _initialize();
    return _hitPointsBonus;
}

void File::setActionPointsBonus(unsigned int actionPointsBonus)
{
    _actionPointsBonus = actionPointsBonus;
}

unsigned int File::actionPointsBonus()
{
    _initialize();
    return _actionPointsBonus;
}

void File::setArmorClassBonus(unsigned int armorClassBonus)
{
    _armorClassBonus = armorClassBonus;
}

unsigned int File::armorClassBonus()
{
    _initialize();
    return _armorClassBonus;
}

void File::setMeleeDamageBonus(unsigned int meleeDamageBonus)
{
    _meleeDamageBonus = meleeDamageBonus;
}

unsigned int File::meleeDamageBonus()
{
    _initialize();
    return _meleeDamageBonus;
}

void File::setCarryWeightBonus(unsigned int carryWeightBonus)
{
    _carryWeightBonus = carryWeightBonus;
}

unsigned int File::carryWeightBonus()
{
    _initialize();
    return _carryWeightBonus;
}

void File::setSequenceBonus(unsigned int sequenceBonus)
{
    _sequenceBonus = sequenceBonus;
}

unsigned int File::sequenceBonus()
{
    _initialize();
    return _sequenceBonus;
}

void File::setHealingRateBonus(unsigned int healingRateBonus)
{
    _healingRateBonus = healingRateBonus;
}

unsigned int File::healingRateBonus()
{
    _initialize();
    return _healingRateBonus;
}

void File::setCriticalChanceBonus(unsigned int criticalChanceBonus)
{
    _criticalChanceBonus = criticalChanceBonus;
}

unsigned int File::criticalChanceBonus()
{
    _initialize();
    return _criticalChanceBonus;
}

void File::setCriticalHitModifierBonus(unsigned int criticalHitModifierBonus)
{
    _criticalHitModifierBonus = criticalHitModifierBonus;
}

unsigned int File::criticalHitModifierBonus()
{
    _initialize();
    return _criticalHitModifierBonus;
}

void File::setRadiationResistanceBonus(unsigned int radiationResistanceBonus)
{
    _radiationResistanceBonus = radiationResistanceBonus;
}

unsigned int File::radiationResistanceBonus()
{
    _initialize();
    return _radiationResistanceBonus;
}

void File::setPoisonResistanceBonus(unsigned int poisonResistanceBonus)
{
    _poisonResistanceBonus = poisonResistanceBonus;
}

unsigned int File::poisonResistanceBonus()
{
    _initialize();
    return _poisonResistanceBonus;
}

void File::setAgeBonus(unsigned int ageBonus)
{
    _ageBonus = ageBonus;
}

unsigned int File::ageBonus()
{
    _initialize();
    return _ageBonus;
}

void File::setGenderBonus(unsigned int genderBonus)
{
    _genderBonus = genderBonus;
}

unsigned int File::genderBonus()
{
    _initialize();
    return _genderBonus;
}

void File::setName(std::string name)
{
    _name = name;
}

std::string File::name()
{
    _initialize();
    return _name;
}

void File::setFirstTaggedSkill(int firstTaggedSkill)
{
    _firstTaggedSkill = firstTaggedSkill;
}

int File::firstTaggedSkill()
{
    _initialize();
    return _firstTaggedSkill;
}

void File::setSecondTaggedSkill(int secondTaggedSkill)
{
    _secondTaggedSkill = secondTaggedSkill;
}

int File::secondTaggedSkill()
{
    _initialize();
    return _secondTaggedSkill;
}

void File::setThirdTaggedSkill(int thirdTaggedSkill)
{
    _thirdTaggedSkill = thirdTaggedSkill;
}

int File::thirdTaggedSkill()
{
    _initialize();
    return _thirdTaggedSkill;
}

void File::setFourthTaggedSkill(int fourthTaggedSkill)
{
    _fourthTaggedSkill = fourthTaggedSkill;
}

int File::fourthTaggedSkill()
{
    _initialize();
    return _fourthTaggedSkill;
}

void File::setFirstTrait(int firstTrait)
{
    _firstTrait = firstTrait;
}

int File::firstTrait()
{
    _initialize();
    return _firstTrait;
}

void File::setSecondTrait(int secondTrait)
{
    _secondTrait = secondTrait;
}

int File::secondTrait()
{
    _initialize();
    return _secondTrait;
}

void File::setCharacterPoints(unsigned int characterPoints)
{
    _characterPoints = characterPoints;
}

unsigned int File::characterPoints()
{
    _initialize();
    return _characterPoints;
}

}
}
