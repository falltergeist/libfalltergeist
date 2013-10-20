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

#ifndef LIBFALLTERGEIST_GCDFILETYPE_H
#define LIBFALLTERGEIST_GCDFILETYPE_H

// C++ standard includes
#include <string>

// libfalltergeist includes

// Third party includes

namespace libfalltergeist
{
class DatFileItem;

class GcdFileType
{
protected:
    DatFileItem * _datFileItem;

    // unknown
    unsigned int _unknown1,
                 _unknown2,
                 _unknown3,
                 _unknown4,
                 _unknown5,
                 _unknown6,
                 _unknown7;
    // primary stats
    unsigned int _strength,
                 _perception,
                 _endurance,
                 _charisma,
                 _intelligence,
                 _agility,
                 _luck;
    // secondary stats
    unsigned int _hitPoints,
                 _actionPoints,
                 _armorClass;
    //unsigned int unknown;
    unsigned int _meleeDamage,
                 _carryWeight,
                 _sequence,
                 _healingRate,
                 _criticalChance,
                 _criticalHitModifier,
                 _damageThresholdNormal,
                 _damageThresholdLaser,
                 _damageThresholdFire,
                 _damageThresholdPlasma,
                 _damageThresholdElectrical,
                 _damageThresholdEMP,
                 _damageThresholdExplosive,
                 _damageResistanceNormal,
                 _damageResistanceLaser,
                 _damageResistanceFire,
                 _damageResistancePlasma,
                 _damageResistanceElectrical,
                 _damageResistanceEMP,
                 _damageResistanceExplosive,
                 _radiationResistance,
                 _poisonResistance,
                 _age,
                 _gender;
    // bonuses to primary stats
    unsigned int _strengthBonus,
                 _perceptionBonus,
                 _enduranceBonus,
                 _charismaBonus,
                 _intelligenceBonus,
                 _agilityBonus,
                 _luckBonus;
    // bonuses to secondaty stats
    unsigned int _hitPointsBonus,
                 _actionPointsBonus,
                 _armorClassBonus;
    //unsigned int unknownBonus;
    unsigned int _meleeDamageBonus,
                 _carryWeightBonus,
                 _sequenceBonus,
                 _healingRateBonus,
                 _criticalChanceBonus,
                 _criticalHitModifierBonus,
                 _damageThresholdNormalBonus,
                 _damageThresholdLaserBonus,
                 _damageThresholdFireBonus,
                 _damageThresholdPlasmaBonus,
                 _damageThresholdElectricalBonus,
                 _damageThresholdEMPBonus,
                 _damageThresholdExplosiveBonus,
                 _damageResistanceNormalBonus,
                 _damageResistanceLaserBonus,
                 _damageResistanceFireBonus,
                 _damageResistancePlasmaBonus,
                 _damageResistanceElectricalBonus,
                 _damageResistanceEMPBonus,
                 _damageResistanceExplosiveBonus,
                 _radiationResistanceBonus,
                 _poisonResistanceBonus,
                 _ageBonus,
                 _genderBonus;
    //skills
    unsigned int _smallGunsSkill,
                 _bigGunsSkill,
                 _energyWeaponsSkill,
                 _unarmedSkill,
                 _meleeWeaponsSkill,
                 _throwingWeaponsSkill,
                 _firstAidSkill,
                 _doctorSkill,
                 _sneakSkill,
                 _lockpickSkill,
                 _stealSkill,
                 _trapsSkill,
                 _scienceSkill,
                 _repairSkill,
                 _speechSkill,
                 _barterSkill,
                 _gamblingSkill,
                 _outdoorsmanSkill;

    std::string _name;

    int _firstTaggedSkill,
        _secondTaggedSkill,
        _thirdTaggedSkill,
        _fourthTaggedSkill,
        _firstTrait,
        _secondTrait;

    unsigned int _characterPoints;

public:
    GcdFileType(DatFileItem * datFileItem);
    ~GcdFileType();

    DatFileItem * datFileItem();

    void open();

    // primary stats
    void setStrength(unsigned int strength);
    unsigned int strength();

    void setPerception(unsigned int perception);
    unsigned int perception();

    void setEndurance(unsigned int endurance);
    unsigned int endurance();

    void setCharisma(unsigned int charisma);
    unsigned int charisma();

    void setIntelligence(unsigned int intelligence);
    unsigned int intelligence();

    void setAgility(unsigned int agility);
    unsigned int agility();

    void setLuck(unsigned int luck);
    unsigned int luck();

    // secondary stats
    void setHitPoints(unsigned int hitPoints);
    unsigned int hitPoints();

    void setActionPoints(unsigned int actionPoints);
    unsigned int actionPoints();

    void setArmorClass(unsigned int armorClass);
    unsigned int armorClass();

    //unsigned int unknown;
    void setMeleeDamage(unsigned int meleeDamage);
    unsigned int meleeDamage();

    void setCarryWeight(unsigned int carryWeight);
    unsigned int carryWeight();

    void setSequence(unsigned int sequence);
    unsigned int sequence();

    void setHealingRate(unsigned int healingRate);
    unsigned int healingRate();

    void setCriticalChance(unsigned int criticalChance);
    unsigned int criticalChance();

    void setCriticalHitModifier(unsigned int criticalHitModifier);
    unsigned int criticalHitModifier();

    void setDamageThresholdNormal(unsigned int damageThresholdNormal);
    unsigned int damageThresholdNormal();

    void setDamageThresholdLaser(unsigned int damageThresholdLaser);
    unsigned int damageThresholdLaser();

    void setDamageThresholdFire(unsigned int damageThresholdFire);
    unsigned int damageThresholdFire();

    void setDamageThresholdPlasma(unsigned int damageThresholdPlasma);
    unsigned int damageThresholdPlasma();

    void setDamageThresholdElectrical(unsigned int damageThresholdElectrical);
    unsigned int damageThresholdElectrical();

    void setDamageThresholdEMP(unsigned int damageThresholdEMP);
    unsigned int damageThresholdEMP();

    void setDamageThresholdExplosive(unsigned int damageThresholdExplosive);
    unsigned int damageThresholdExplosive();

    void setDamageResistanceNormal(unsigned int damageResistanceNormal);
    unsigned int damageResistanceNormal();

    void setDamageResistanceLaser(unsigned int damageResistanceLaser);
    unsigned int damageResistanceLaser();

    void setDamageResistanceFire(unsigned int damageResistanceFire);
    unsigned int damageResistanceFire();

    void setDamageResistancePlasma(unsigned int damageResistancePlasma);
    unsigned int damageResistancePlasma();

    void setDamageResistanceElectrical(unsigned int damageResistanceElectrical);
    unsigned int damageResistanceElectrical();

    void setDamageResistanceEMP(unsigned int damageResistanceEMP);
    unsigned int damageResistanceEMP();

    void setDamageResistanceExplosive(unsigned int damageResistanceExplosive);
    unsigned int damageResistanceExplosive();

    void setRadiationResistance(unsigned int radiationResistance);
    unsigned int radiationResistance();

    void setPoisonResistance(unsigned int poisonResistance);
    unsigned int poisonResistance();

    void setAge(unsigned int age);
    unsigned int age();

    void setGender(unsigned int gender);
    unsigned int gender();

    // bonuses to primary stats
    void setStrengthBonus(unsigned int strengthBonus);
    unsigned int strengthBonus();

    void setPerceptionBonus(unsigned int perceptionBonus);
    unsigned int perceptionBonus();

    void setEnduranceBonus(unsigned int enduranceBonus);
    unsigned int enduranceBonus();

    void setCharismaBonus(unsigned int charismaBonus);
    unsigned int charismaBonus();

    void setIntelligenceBonus(unsigned int intelligenceBonus);
    unsigned int intelligenceBonus();

    void setAgilityBonus(unsigned int agilityBonus);
    unsigned int agilityBonus();

    void setLuckBonus(unsigned int luckBonus);
    unsigned int luckBonus();

    // bonuses to secondaty stats
    void setHitPointsBonus(unsigned int hitPointsBonus);
    unsigned int hitPointsBonus();

    void setActionPointsBonus(unsigned int actionPointsBonus);
    unsigned int actionPointsBonus();

    void setArmorClassBonus(unsigned int armorClassBonus);
    unsigned int armorClassBonus();

    //unsigned int unknownBonus;

    void setMeleeDamageBonus(unsigned int meleeDamageBonus);
    unsigned int meleeDamageBonus();

    void setCarryWeightBonus(unsigned int carryWeightBonus);
    unsigned int carryWeightBonus();

    void setSequenceBonus(unsigned int sequenceBonus);
    unsigned int sequenceBonus();

    void setHealingRateBonus(unsigned int healingRateBonus);
    unsigned int healingRateBonus();

    void setCriticalChanceBonus(unsigned int criticalChanceBonus);
    unsigned int criticalChanceBonus();

    void setCriticalHitModifierBonus(unsigned int criticalHitModifierBonus);
    unsigned int criticalHitModifierBonus();

    void setDamageThresholdNormalBonus(unsigned int damageThresholdNormalBonus);
    unsigned int damageThresholdNormalBonus();

    void setDamageThresholdLaserBonus(unsigned int damageThresholdLaserBonus);
    unsigned int damageThresholdLaserBonus();

    void setDamageThresholdFireBonus(unsigned int damageThresholdFireBonus);
    unsigned int damageThresholdFireBonus();

    void setDamageThresholdPlasmaBonus(unsigned int damageThresholdPlasmaBonus);
    unsigned int damageThresholdPlasmaBonus();

    void setDamageThresholdElectricalBonus(unsigned int damageThresholdElectricalBonus);
    unsigned int damageThresholdElectricalBonus();    

    void setDamageThresholdEMPBonus(unsigned int damageThresholdEMPBonus);
    unsigned int damageThresholdEMPBonus();

    void setDamageThresholdExplosiveBonus(unsigned int damageThresholdExplosiveBonus);
    unsigned int damageThresholdExplosiveBonus();

    void setDamageResistanceNormalBonus(unsigned int damageResistanceNormalBonus);
    unsigned int damageResistanceNormalBonus();

    void setDamageResistanceLaserBonus(unsigned int damageResistanceLaserBonus);
    unsigned int damageResistanceLaserBonus();

    void setDamageResistanceFireBonus(unsigned int damageResistanceFireBonus);
    unsigned int damageResistanceFireBonus();

    void setDamageResistancePlasmaBonus(unsigned int damageResistancePlasmaBonus);
    unsigned int damageResistancePlasmaBonus();

    void setDamageResistanceElectricalBonus(unsigned int damageResistanceElectricalBonus);
    unsigned int damageResistanceElectricalBonus();

    void setDamageResistanceEMPBonus(unsigned int damageResistanceEMPBonus);
    unsigned int damageResistanceEMPBonus();

    void setDamageResistanceExplosiveBonus(unsigned int damageResistanceExplosiveBonus);
    unsigned int damageResistanceExplosiveBonus();

    void setRadiationResistanceBonus(unsigned int radiationResistanceBonus);
    unsigned int radiationResistanceBonus();

    void setPoisonResistanceBonus(unsigned int poisonResistanceBonus);
    unsigned int poisonResistanceBonus();

    void setAgeBonus(unsigned int ageBonus);
    unsigned int ageBonus();

    void setGenderBonus(unsigned int genderBonus);
    unsigned int genderBonus();

    //skills
    void setSmallGunsSkill(unsigned int smallGunsSkill);
    unsigned int smallGunsSkill();

    void setBigGunsSkill(unsigned int bigGunsSkill);
    unsigned int bigGunsSkill();

    void setEnergyWeaponsSkill(unsigned int energyWeaponsSkill);
    unsigned int energyWeaponsSkill();

    void setUnarmedSkill(unsigned int unarmedSkill);
    unsigned int unarmedSkill();

    void setMeleeWeaponsSkill(unsigned int meleeWeaponsSkill);
    unsigned int meleeWeaponsSkill();

    void setThrowingWeaponsSkill(unsigned int throwingWeaponsSkill);
    unsigned int throwingWeaponsSkill();

    void setFirstAidSkill(unsigned int firstAidSkill);
    unsigned int firstAidSkill();

    void setDoctorSkill(unsigned int doctorSkill);
    unsigned int doctorSkill();

    void setSneakSkill(unsigned int sneakSkill);
    unsigned int sneakSkill();

    void setLockpickSkill(unsigned int lockpickSkill);
    unsigned int lockpickSkill();

    void setStealSkill(unsigned int stealSkill);
    unsigned int stealSkill();

    void setTrapsSkill(unsigned int trapsSkill);
    unsigned int trapsSkill();

    void setScienceSkill(unsigned int scienceSkill);
    unsigned int scienceSkill();

    void setRepairSkill(unsigned int repairSkill);
    unsigned int repairSkill();

    void setSpeechSkill(unsigned int speechSkill);
    unsigned int speechSkill();

    void setBarterSkill(unsigned int barterSkill);
    unsigned int barterSkill();

    void setGamblingSkill(unsigned int gamblingSkill);
    unsigned int gamblingSkill();

    void setOutdoorsmanSkill(unsigned int outdoorsmanSkill);
    unsigned int outdoorsmanSkill();

    void setName(std::string name);
    std::string name();

    void setFirstTaggedSkill(int firstTaggedSkill);
    int firstTaggedSkill();

    void setSecondTaggedSkill(int secondTaggedSkill);
    int secondTaggedSkill();

    void setThirdTaggedSkill(int thirdTaggedSkill);
    int thirdTaggedSkill();

    void setFourthTaggedSkill(int fourthTaggedSkill);
    int fourthTaggedSkill();

    void setFirstTrait(int firstTrait);
    int firstTrait();

    void setSecondTrait(int secondTrait);
    int secondTrait();

    void setCharacterPoints(unsigned int characterPoints);
    unsigned int characterPoints();
};

}
#endif // LIBFALLTERGEIST_GCDFILETYPE_H
