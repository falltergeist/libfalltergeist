/*
 * Copyright 2012-2013 Falltergeist Developers.
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

#include "../src/GcdFileType.h"
#include "../src/DatFileItem.h"
#include <cstring>

namespace libfalltergeist
{

GcdFileType::GcdFileType(DatFileItem * datFileItem) : _datFileItem(datFileItem)
{
    _name = 0;
    open();
}

GcdFileType::~GcdFileType()
{
    delete [] _name;
}

void GcdFileType::open()
{
    datFileItem()->setPosition(0);
    // unknown 4 bytes
    datFileItem()->skipBytes(4);
    // primary stats
    setStrength(datFileItem()->readUint32());
    setPerception(datFileItem()->readUint32());
    setEndurance(datFileItem()->readUint32());
    setCharisma(datFileItem()->readUint32());
    setIntelligence(datFileItem()->readUint32());
    setAgility(datFileItem()->readUint32());
    setLuck(datFileItem()->readUint32());

    // secondary stats
    setHitPoints(datFileItem()->readUint32());
    setActionPoints(datFileItem()->readUint32());
    setArmorClass(datFileItem()->readUint32());

    // unknown
    datFileItem()->skipBytes(4);
    setMeleeDamage(datFileItem()->readUint32());
    setCarryWeight(datFileItem()->readUint32());
    setSequence(datFileItem()->readUint32());
    setHealingRate(datFileItem()->readUint32());
    setCriticalChance(datFileItem()->readUint32());
    setCriticalHitModifier(datFileItem()->readUint32());
    setDamageThresholdNormal(datFileItem()->readUint32());
    setDamageThresholdLaser(datFileItem()->readUint32());
    setDamageThresholdFire(datFileItem()->readUint32());
    setDamageThresholdPlasma(datFileItem()->readUint32());
    setDamageThresholdElectrical(datFileItem()->readUint32());
    setDamageThresholdEMP(datFileItem()->readUint32());
    setDamageThresholdExplosive(datFileItem()->readUint32());
    setDamageResistanceNormal(datFileItem()->readUint32());
    setDamageResistanceLaser(datFileItem()->readUint32());
    setDamageResistanceFire(datFileItem()->readUint32());
    setDamageResistancePlasma(datFileItem()->readUint32());
    setDamageResistanceElectrical(datFileItem()->readUint32());
    setDamageResistanceEMP(datFileItem()->readUint32());
    setDamageResistanceExplosive(datFileItem()->readUint32());
    setRadiationResistance(datFileItem()->readUint32());
    setPoisonResistance(datFileItem()->readUint32());
    setAge(datFileItem()->readUint32());
    setGender(datFileItem()->readUint32());

    // bonuses to primary stats
    setStrengthBonus(datFileItem()->readUint32());
    setPerceptionBonus(datFileItem()->readUint32());
    setEnduranceBonus(datFileItem()->readUint32());
    setCharismaBonus(datFileItem()->readUint32());
    setIntelligenceBonus(datFileItem()->readUint32());
    setAgilityBonus(datFileItem()->readUint32());
    setLuckBonus(datFileItem()->readUint32());

    // bonuses to secondary stats
    setHitPointsBonus(datFileItem()->readUint32());
    setActionPointsBonus(datFileItem()->readUint32());
    setArmorClassBonus(datFileItem()->readUint32());

    // unknown bonus
    datFileItem()->skipBytes(4);

    setMeleeDamageBonus(datFileItem()->readUint32());
    setCarryWeightBonus(datFileItem()->readUint32());
    setSequenceBonus(datFileItem()->readUint32());
    setHealingRateBonus(datFileItem()->readUint32());
    setCriticalChanceBonus(datFileItem()->readUint32());
    setCriticalHitModifierBonus(datFileItem()->readUint32());
    setDamageThresholdNormalBonus(datFileItem()->readUint32());
    setDamageThresholdLaserBonus(datFileItem()->readUint32());
    setDamageThresholdFireBonus(datFileItem()->readUint32());
    setDamageThresholdPlasmaBonus(datFileItem()->readUint32());
    setDamageThresholdElectricalBonus(datFileItem()->readUint32());
    setDamageThresholdEMPBonus(datFileItem()->readUint32());
    setDamageThresholdExplosiveBonus(datFileItem()->readUint32());
    setDamageResistanceNormalBonus(datFileItem()->readUint32());
    setDamageResistanceLaserBonus(datFileItem()->readUint32());
    setDamageResistanceFireBonus(datFileItem()->readUint32());
    setDamageResistancePlasmaBonus(datFileItem()->readUint32());
    setDamageResistanceElectricalBonus(datFileItem()->readUint32());
    setDamageResistanceEMPBonus(datFileItem()->readUint32());
    setDamageResistanceExplosiveBonus(datFileItem()->readUint32());
    setRadiationResistanceBonus(datFileItem()->readUint32());
    setPoisonResistanceBonus(datFileItem()->readUint32());
    setAgeBonus(datFileItem()->readUint32());
    setGenderBonus(datFileItem()->readUint32());

    //skills
    setSmallGunsSkill(datFileItem()->readUint32());
    setBigGunsSkill(datFileItem()->readUint32());
    setEnergyWeaponsSkill(datFileItem()->readUint32());
    setUnarmedSkill(datFileItem()->readUint32());
    setMeleeWeaponsSkill(datFileItem()->readUint32());
    setThrowingWeaponsSkill(datFileItem()->readUint32());
    setFirstAidSkill(datFileItem()->readUint32());
    setDoctorSkill(datFileItem()->readUint32());
    setSneakSkill(datFileItem()->readUint32());
    setLockpickSkill(datFileItem()->readUint32());
    setStealSkill(datFileItem()->readUint32());
    setTrapsSkill(datFileItem()->readUint32());
    setScienceSkill(datFileItem()->readUint32());
    setRepairSkill(datFileItem()->readUint32());
    setSpeechSkill(datFileItem()->readUint32());
    setBarterSkill(datFileItem()->readUint32());
    setGamblingSkill(datFileItem()->readUint32());
    setOutdoorsmanSkill(datFileItem()->readUint32());

    // unknown
    datFileItem()->skipBytes(16);

    // name
    char * name = new char[32];
    datFileItem()->readBytes(name, 32);
    setName(name);
    delete [] name;

    setFirstTaggedSkill(datFileItem()->readUint32());
    setSecondTaggedSkill(datFileItem()->readUint32());
    setThirdTaggedSkill(datFileItem()->readUint32());
    setFourthTaggedSkill(datFileItem()->readUint32());
    setFirstTrait(datFileItem()->readUint32());
    setSecondTrait(datFileItem()->readUint32());
    setCharacterPoints(datFileItem()->readUint32());
}

DatFileItem * GcdFileType::datFileItem()
{
    return _datFileItem;
}

void GcdFileType::setStrength(unsigned int strength)
{
    _strength = strength;
}

unsigned int GcdFileType::strength()
{
    return _strength;
}

void GcdFileType::setPerception(unsigned int perception)
{
    _perception = perception;
}

unsigned int GcdFileType::perception()
{
    return _perception;
}

void GcdFileType::setEndurance(unsigned int endurance)
{
    _endurance = endurance;
}

unsigned int GcdFileType::endurance()
{
    return _endurance;
}

void GcdFileType::setCharisma(unsigned int charisma)
{
    _charisma = charisma;
}

unsigned int GcdFileType::charisma()
{
    return _charisma;
}

void GcdFileType::setIntelligence(unsigned int intelligence)
{
    _intelligence = intelligence;
}

unsigned int GcdFileType::intelligence()
{
    return _intelligence;
}

void GcdFileType::setAgility(unsigned int agility)
{
    _agility = agility;
}

unsigned int GcdFileType::agility()
{
    return _agility;
}

void GcdFileType::setLuck(unsigned int luck)
{
    _luck = luck;
}

unsigned int GcdFileType::luck()
{
    return _luck;
}

void GcdFileType::setHitPoints(unsigned int hitPoints)
{
    _hitPoints = hitPoints;
}

unsigned int GcdFileType::hitPoints()
{
    return _hitPoints;
}

void GcdFileType::setActionPoints(unsigned int actionPoints)
{
    _actionPoints = actionPoints;
}

unsigned int GcdFileType::actionPoints()
{
    return _actionPoints;
}

void GcdFileType::setArmorClass(unsigned int armorClass)
{
    _armorClass = armorClass;
}

unsigned int GcdFileType::armorClass()
{
    return _armorClass;
}

unsigned int GcdFileType::meleeDamage()
{
    return _meleeDamage;
}

unsigned int GcdFileType::carryWeight()
{
    return _carryWeight;
}

unsigned int GcdFileType::sequence()
{
    return _sequence;
}

unsigned int GcdFileType::healingRate()
{
    return _healingRate;
}

unsigned int GcdFileType::criticalChance()
{
    return _criticalChance;
}

unsigned int GcdFileType::criticalHitModifier()
{
    return _criticalHitModifier;
}

unsigned int GcdFileType::damageThresholdNormal()
{
    return _damageThresholdNormal;
}

unsigned int GcdFileType::damageThresholdLaser()
{
    return _damageThresholdLaser;
}

unsigned int GcdFileType::damageThresholdFire()
{
    return _damageThresholdFire;
}

unsigned int GcdFileType::damageThresholdPlasma()
{
    return _damageThresholdPlasma;
}

unsigned int GcdFileType::damageThresholdElectrical()
{
    return _damageThresholdElectrical;
}

unsigned int GcdFileType::damageThresholdEMP()
{
    return _damageThresholdEMP;
}

unsigned int GcdFileType::damageThresholdExplosive()
{
    return _damageThresholdExplosive;
}

unsigned int GcdFileType::damageResistanceNormal()
{
    return _damageResistanceNormal;
}

unsigned int GcdFileType::damageResistanceLaser()
{
    return _damageResistanceLaser;
}

unsigned int GcdFileType::damageResistanceFire()
{
    return _damageResistanceFire;
}

unsigned int GcdFileType::damageResistancePlasma()
{
    return _damageResistancePlasma;
}

unsigned int GcdFileType::damageResistanceElectrical()
{
    return _damageResistanceElectrical;
}

unsigned int GcdFileType::damageResistanceEMP()
{
    return _damageResistanceEMP;
}

unsigned int GcdFileType::damageResistanceExplosive()
{
    return _damageResistanceExplosive;
}

unsigned int GcdFileType::radiationResistance()
{
    return _radiationResistance;
}

unsigned int GcdFileType::poisonResistance()
{
    return _poisonResistance;
}

unsigned int GcdFileType::age()
{
    return _age;
}

unsigned int GcdFileType::gender()
{
    return _gender;
}

unsigned int GcdFileType::strengthBonus()
{
    return _strengthBonus;
}

unsigned int GcdFileType::perceptionBonus()
{
    return _perceptionBonus;
}

unsigned int GcdFileType::enduranceBonus()
{
    return _enduranceBonus;
}

unsigned int GcdFileType::charismaBonus()
{
    return _charismaBonus;
}

unsigned int GcdFileType::intelligenceBonus()
{
    return _intelligenceBonus;
}

unsigned int GcdFileType::agilityBonus()
{
    return _agilityBonus;
}

unsigned int GcdFileType::luckBonus()
{
    return _luckBonus;
}

unsigned int GcdFileType::hitPointsBonus()
{
    return _hitPointsBonus;
}

unsigned int GcdFileType::actionPointsBonus()
{
    return _actionPointsBonus;
}

unsigned int GcdFileType::armorClassBonus()
{
    return _armorClassBonus;
}

unsigned int GcdFileType::meleeDamageBonus()
{
    return _meleeDamageBonus;
}

unsigned int GcdFileType::carryWeightBonus()
{
    return _carryWeightBonus;
}

unsigned int GcdFileType::sequenceBonus()
{
    return _sequenceBonus;
}

unsigned int GcdFileType::healingRateBonus()
{
    return _healingRateBonus;
}

unsigned int GcdFileType::criticalChanceBonus()
{
    return _criticalChanceBonus;
}

unsigned int GcdFileType::criticalHitModifierBonus()
{
    return _criticalHitModifierBonus;
}

unsigned int GcdFileType::damageThresholdNormalBonus()
{
    return _damageThresholdNormalBonus;
}

unsigned int GcdFileType::damageThresholdLaserBonus()
{
    return _damageThresholdLaserBonus;
}

unsigned int GcdFileType::damageThresholdFireBonus()
{
    return _damageThresholdFireBonus;
}

unsigned int GcdFileType::damageThresholdPlasmaBonus()
{
    return _damageThresholdPlasmaBonus;
}

unsigned int GcdFileType::damageThresholdElectricalBonus()
{
    return _damageThresholdElectricalBonus;
}

unsigned int GcdFileType::damageThresholdEMPBonus()
{
    return _damageThresholdEMPBonus;
}

unsigned int GcdFileType::damageThresholdExplosiveBonus()
{
    return _damageThresholdExplosiveBonus;
}

unsigned int GcdFileType::damageResistanceNormalBonus()
{
    return _damageResistanceNormalBonus;
}

unsigned int GcdFileType::damageResistanceLaserBonus()
{
    return _damageResistanceLaserBonus;
}

unsigned int GcdFileType::damageResistanceFireBonus()
{
    return _damageResistanceFireBonus;
}

unsigned int GcdFileType::damageResistancePlasmaBonus()
{
    return _damageResistancePlasmaBonus;
}

unsigned int GcdFileType::damageResistanceElectricalBonus()
{
    return _damageResistanceElectricalBonus;
}

unsigned int GcdFileType::damageResistanceEMPBonus()
{
    return _damageResistanceEMPBonus;
}

unsigned int GcdFileType::damageResistanceExplosiveBonus()
{
    return _damageResistanceExplosiveBonus;
}

unsigned int GcdFileType::radiationResistanceBonus()
{
    return _radiationResistanceBonus;
}

unsigned int GcdFileType::poisonResistanceBonus()
{
    return _poisonResistanceBonus;
}

unsigned int GcdFileType::ageBonus()
{
    return _ageBonus;
}

unsigned int GcdFileType::genderBonus()
{
    return _genderBonus;
}

unsigned int GcdFileType::smallGunsSkill()
{
    return _smallGunsSkill;
}

unsigned int GcdFileType::bigGunsSkill()
{
    return _bigGunsSkill;
}

unsigned int GcdFileType::energyWeaponsSkill()
{
    return _energyWeaponsSkill;
}

unsigned int GcdFileType::unarmedSkill()
{
    return _unarmedSkill;
}

unsigned int GcdFileType::meleeWeaponsSkill()
{
    return _meleeWeaponsSkill;
}

unsigned int GcdFileType::throwingWeaponsSkill()
{
    return _throwingWeaponsSkill;
}

unsigned int GcdFileType::firstAidSkill()
{
    return _firstAidSkill;
}

unsigned int GcdFileType::doctorSkill()
{
    return _doctorSkill;
}

unsigned int GcdFileType::sneakSkill()
{
    return _sneakSkill;
}

unsigned int GcdFileType::lockpickSkill()
{
    return _lockpickSkill;
}

unsigned int GcdFileType::stealSkill()
{
    return _stealSkill;
}

unsigned int GcdFileType::trapsSkill()
{
    return _trapsSkill;
}

unsigned int GcdFileType::scienceSkill()
{
    return _scienceSkill;
}

unsigned int GcdFileType::repairSkill()
{
    return _repairSkill;
}

unsigned int GcdFileType::speechSkill()
{
    return _speechSkill;
}

unsigned int GcdFileType::barterSkill()
{
    return _barterSkill;
}

unsigned int GcdFileType::gamblingSkill()
{
    return _gamblingSkill;
}

unsigned int GcdFileType::outdoorsmanSkill()
{
    return _outdoorsmanSkill;
}

void GcdFileType::setName(const char * name)
{
    delete [] _name;
    _name = new char[strlen(name) + 1]();
    strcpy(_name, name);
}

const char * GcdFileType::name()
{
    return _name;
}

unsigned int GcdFileType::firstTaggedSkill()
{
    return _firstTaggedSkill;
}

unsigned int GcdFileType::secondTaggedSkill()
{
    return _secondTaggedSkill;
}

unsigned int GcdFileType::thirdTaggedSkill()
{
    return _thirdTaggedSkill;
}

unsigned int GcdFileType::fourthTaggedSkill()
{
    return _fourthTaggedSkill;
}

unsigned int GcdFileType::firstTrait()
{
    return _firstTrait;
}

unsigned int GcdFileType::secondTrait()
{
    return _secondTrait;
}

unsigned int GcdFileType::characterPoints()
{
    return _characterPoints;
}
































}
