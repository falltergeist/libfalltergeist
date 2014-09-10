/*
 * Copyright 2012-2014 Falltergeist Developers.
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
#include "../src/GcdFileType.h"
#include "../src/Exception.h"

// Third party includes

namespace libfalltergeist
{

GcdFileType::GcdFileType(std::shared_ptr<DatFileEntry> datFileEntry) : DatFileItem(datFileEntry)
{
}

GcdFileType::GcdFileType(std::ifstream * stream) : DatFileItem(stream)
{
}

GcdFileType::~GcdFileType()
{
}

void GcdFileType::_initialize()
{
    if (_initialized) return;
    DatFileItem::_initialize();
    DatFileItem::setPosition(0);

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

    *this >> _meleeDamageBonus >> _carryWeightBonus >> _sequenceBonus >> _healingRateBonus
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

    *this >> _firstTaggedSkill
          >> _secondTaggedSkill
          >> _thirdTaggedSkill
          >> _fourthTaggedSkill
          >> _firstTrait
          >> _secondTrait
          >> _characterPoints;
}

unsigned int GcdFileType::stat(unsigned int number)
{
    if (number > 6) throw Exception("GcdFileType::stat() - number out of range: " + std::to_string(number));
    _initialize();
    return _stats.at(number);
}

void GcdFileType::setStat(unsigned int number, unsigned int value)
{
    if (number > 6) throw Exception("GcdFileType::setStat() - number out of range: " + std::to_string(number));
    _stats.at(number) = value;
}

unsigned int GcdFileType::statBonus(unsigned int number)
{
    if (number > 6) throw Exception("GcdFileType::statBonus() - number out of range: " + std::to_string(number));
    _initialize();
    return _statsBonus.at(number);
}

void GcdFileType::setStatBonus(unsigned int number, unsigned int value)
{
    if (number > 6) throw Exception("GcdFileType::setStatBonus() - number out of range: " + std::to_string(number));
    _statsBonus.at(number) = value;
}

unsigned int GcdFileType::skill(unsigned int number)
{
    if (number > 17) throw Exception("GcdFileType::skill() - number out of range: " + std::to_string(number));
    _initialize();
    return _skills.at(number);
}

void GcdFileType::setSkill(unsigned int number, unsigned int value)
{
    if (number > 17) throw Exception("GcdFileType::setSkill() - number out of range: " + std::to_string(number));
    _skills.at(number) = value;
}

unsigned int GcdFileType::damage(unsigned int type)
{
    if (type > 6) throw Exception("GcdFileType::damage() - type out of range: " + std::to_string(type));
    _initialize();
    return _damage.at(type);
}

void GcdFileType::setDamage(unsigned int type, unsigned int value)
{
    if (type > 6) throw Exception("GcdFileType::setDamage() - type out of range: " + std::to_string(type));
    _damage.at(type) = value;    
}

unsigned int GcdFileType::damageBonus(unsigned int type)
{
    if (type > 6) throw Exception("GcdFileType::damageBonus() - type out of range: " + std::to_string(type));
    _initialize();
    return _damageBonus.at(type);
}

void GcdFileType::setDamageBonus(unsigned int type, unsigned int value)
{
    if (type > 6) throw Exception("GcdFileType::setDamageBonus() - type out of range: " + std::to_string(type));
    _damageBonus.at(type) = value;    
}

unsigned int GcdFileType::resistance(unsigned int type)
{
    if (type > 6) throw Exception("GcdFileType::resistance() - type out of range: " + std::to_string(type));
    _initialize();
    return _resistance.at(type);
}

void GcdFileType::setResistance(unsigned int type, unsigned int value)
{
    if (type > 6) throw Exception("GcdFileType::setResistance() - type out of range: " + std::to_string(type));
    _resistance.at(type) = value;
}

unsigned int GcdFileType::resistanceBonus(unsigned int type)
{
    if (type > 6) throw Exception("GcdFileType::resistanceBonus() - type out of range: " + std::to_string(type));
    _initialize();
    return _resistanceBonus.at(type);
}

void GcdFileType::setResistanceBonus(unsigned int type, unsigned int value)
{
    if (type > 6) throw Exception("GcdFileType::setResistanceBonus() - type out of range: " + std::to_string(type));
    _resistanceBonus.at(type) = value;
}

void GcdFileType::setHitPoints(unsigned int hitPoints)
{
    _hitPoints = hitPoints;
}

unsigned int GcdFileType::hitPoints()
{
    _initialize();
    return _hitPoints;
}

void GcdFileType::setActionPoints(unsigned int actionPoints)
{
    _actionPoints = actionPoints;
}

unsigned int GcdFileType::actionPoints()
{
    _initialize();
    return _actionPoints;
}

void GcdFileType::setArmorClass(unsigned int armorClass)
{
    _armorClass = armorClass;
}

unsigned int GcdFileType::armorClass()
{
    _initialize();
    return _armorClass;
}

void GcdFileType::setMeleeDamage(unsigned int meleeDamage)
{
    _meleeDamage = meleeDamage;
}

unsigned int GcdFileType::meleeDamage()
{
    _initialize();
    return _meleeDamage;
}

void GcdFileType::setCarryWeight(unsigned int carryWeight)
{
    _carryWeight = carryWeight;
}

unsigned int GcdFileType::carryWeight()
{
    _initialize();
    return _carryWeight;
}

void GcdFileType::setSequence(unsigned int sequence)
{
    _sequence = sequence;
}

unsigned int GcdFileType::sequence()
{
    _initialize();
    return _sequence;
}

void GcdFileType::setHealingRate(unsigned int healingRate)
{
    _healingRate = healingRate;
}

unsigned int GcdFileType::healingRate()
{
    _initialize();
    return _healingRate;
}

void GcdFileType::setCriticalChance(unsigned int criticalChance)
{
    _criticalChance = criticalChance;
}

unsigned int GcdFileType::criticalChance()
{
    _initialize();
    return _criticalChance;
}

void GcdFileType::setCriticalHitModifier(unsigned int criticalHitModifier)
{
    _criticalHitModifier = criticalHitModifier;
}

unsigned int GcdFileType::criticalHitModifier()
{
    _initialize();
    return _criticalHitModifier;
}

void GcdFileType::setRadiationResistance(unsigned int radiationResistance)
{
    _radiationResistance = radiationResistance;
}

unsigned int GcdFileType::radiationResistance()
{
    _initialize();
    return _radiationResistance;
}

void GcdFileType::setPoisonResistance(unsigned int poisonResistance)
{
    _poisonResistance = poisonResistance;
}

unsigned int GcdFileType::poisonResistance()
{
    _initialize();
    return _poisonResistance;
}

void GcdFileType::setAge(unsigned int age)
{
    _age = age;
}

unsigned int GcdFileType::age()
{
    _initialize();
    return _age;
}

void GcdFileType::setGender(unsigned int gender)
{
    _gender = gender;
}

unsigned int GcdFileType::gender()
{
    _initialize();
    return _gender;
}

void GcdFileType::setHitPointsBonus(unsigned int hitPointsBonus)
{
    _hitPointsBonus = hitPointsBonus;
}

unsigned int GcdFileType::hitPointsBonus()
{
    _initialize();
    return _hitPointsBonus;
}

void GcdFileType::setActionPointsBonus(unsigned int actionPointsBonus)
{
    _actionPointsBonus = actionPointsBonus;
}

unsigned int GcdFileType::actionPointsBonus()
{
    _initialize();
    return _actionPointsBonus;
}

void GcdFileType::setArmorClassBonus(unsigned int armorClassBonus)
{
    _armorClassBonus = armorClassBonus;
}

unsigned int GcdFileType::armorClassBonus()
{
    _initialize();
    return _armorClassBonus;
}

void GcdFileType::setMeleeDamageBonus(unsigned int meleeDamageBonus)
{
    _meleeDamageBonus = meleeDamageBonus;
}

unsigned int GcdFileType::meleeDamageBonus()
{
    _initialize();
    return _meleeDamageBonus;
}

void GcdFileType::setCarryWeightBonus(unsigned int carryWeightBonus)
{
    _carryWeightBonus = carryWeightBonus;
}

unsigned int GcdFileType::carryWeightBonus()
{
    _initialize();
    return _carryWeightBonus;
}

void GcdFileType::setSequenceBonus(unsigned int sequenceBonus)
{
    _sequenceBonus = sequenceBonus;
}

unsigned int GcdFileType::sequenceBonus()
{
    _initialize();
    return _sequenceBonus;
}

void GcdFileType::setHealingRateBonus(unsigned int healingRateBonus)
{
    _healingRateBonus = healingRateBonus;
}

unsigned int GcdFileType::healingRateBonus()
{
    _initialize();
    return _healingRateBonus;
}

void GcdFileType::setCriticalChanceBonus(unsigned int criticalChanceBonus)
{
    _criticalChanceBonus = criticalChanceBonus;
}

unsigned int GcdFileType::criticalChanceBonus()
{
    _initialize();
    return _criticalChanceBonus;
}

void GcdFileType::setCriticalHitModifierBonus(unsigned int criticalHitModifierBonus)
{
    _criticalHitModifierBonus = criticalHitModifierBonus;
}

unsigned int GcdFileType::criticalHitModifierBonus()
{
    _initialize();
    return _criticalHitModifierBonus;
}

void GcdFileType::setRadiationResistanceBonus(unsigned int radiationResistanceBonus)
{
    _radiationResistanceBonus = radiationResistanceBonus;
}

unsigned int GcdFileType::radiationResistanceBonus()
{
    _initialize();
    return _radiationResistanceBonus;
}

void GcdFileType::setPoisonResistanceBonus(unsigned int poisonResistanceBonus)
{
    _poisonResistanceBonus = poisonResistanceBonus;
}

unsigned int GcdFileType::poisonResistanceBonus()
{
    _initialize();
    return _poisonResistanceBonus;
}

void GcdFileType::setAgeBonus(unsigned int ageBonus)
{
    _ageBonus = ageBonus;
}

unsigned int GcdFileType::ageBonus()
{
    _initialize();
    return _ageBonus;
}

void GcdFileType::setGenderBonus(unsigned int genderBonus)
{
    _genderBonus = genderBonus;
}

unsigned int GcdFileType::genderBonus()
{
    _initialize();
    return _genderBonus;
}

void GcdFileType::setName(std::string name)
{
    _name = name;
}

std::string GcdFileType::name()
{
    _initialize();
    return _name;
}

void GcdFileType::setFirstTaggedSkill(int firstTaggedSkill)
{
    _firstTaggedSkill = firstTaggedSkill;
}

int GcdFileType::firstTaggedSkill()
{
    _initialize();
    return _firstTaggedSkill;
}

void GcdFileType::setSecondTaggedSkill(int secondTaggedSkill)
{
    _secondTaggedSkill = secondTaggedSkill;
}

int GcdFileType::secondTaggedSkill()
{
    _initialize();
    return _secondTaggedSkill;
}

void GcdFileType::setThirdTaggedSkill(int thirdTaggedSkill)
{
    _thirdTaggedSkill = thirdTaggedSkill;
}

int GcdFileType::thirdTaggedSkill()
{
    _initialize();
    return _thirdTaggedSkill;
}

void GcdFileType::setFourthTaggedSkill(int fourthTaggedSkill)
{
    _fourthTaggedSkill = fourthTaggedSkill;
}

int GcdFileType::fourthTaggedSkill()
{
    _initialize();
    return _fourthTaggedSkill;
}

void GcdFileType::setFirstTrait(int firstTrait)
{
    _firstTrait = firstTrait;
}

int GcdFileType::firstTrait()
{
    _initialize();
    return _firstTrait;
}

void GcdFileType::setSecondTrait(int secondTrait)
{
    _secondTrait = secondTrait;
}

int GcdFileType::secondTrait()
{
    _initialize();
    return _secondTrait;
}

void GcdFileType::setCharacterPoints(unsigned int characterPoints)
{
     _characterPoints = characterPoints;
}

unsigned int GcdFileType::characterPoints()
{
    _initialize();
    return _characterPoints;
}
































}
