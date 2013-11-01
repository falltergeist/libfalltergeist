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
#include <vector>

// libfalltergeist includes
#include "../src/DatFileItem.h"

// Third party includes

namespace libfalltergeist
{

class GcdFileType : public DatFileItem
{
protected:
    // unknown
    unsigned int _unknown1,
                 _unknown2,
                 _unknown3,
                 _unknown4,
                 _unknown5,
                 _unknown6,
                 _unknown7;
    // primary stats
    std::vector<unsigned int> _stats = {0, 0, 0, 0, 0, 0, 0};
    // bonuses to primary stats
    std::vector<unsigned int> _statsBonus = {0, 0, 0, 0, 0, 0, 0};    
    // skills
    std::vector<unsigned int> _skills = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // damage
    std::vector<unsigned int> _damage = {0, 0, 0, 0, 0, 0, 0};
    std::vector<unsigned int> _damageBonus = {0, 0, 0, 0, 0, 0, 0};
    // resistance
    std::vector<unsigned int> _resistance = {0, 0, 0, 0, 0, 0, 0};
    std::vector<unsigned int> _resistanceBonus = {0, 0, 0, 0, 0, 0, 0};
    
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
                 _radiationResistance,
                 _poisonResistance,
                 _age,
                 _gender;
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
                 _radiationResistanceBonus,
                 _poisonResistanceBonus,
                 _ageBonus,
                 _genderBonus;

    std::string _name;

    int _firstTaggedSkill,
        _secondTaggedSkill,
        _thirdTaggedSkill,
        _fourthTaggedSkill,
        _firstTrait,
        _secondTrait;

    unsigned int _characterPoints;

    virtual void _initialize();
public:
    enum {STATS_STRENGTH = 0, STATS_PERCEPTION, STATS_ENDURANCE, STATS_CHARISMA, STATS_INTELLIGENCE, STATS_AGILITY, STATS_LUCK };
    enum { SKILLS_1 = 0, // Small Guns
           SKILLS_2, // Big Guns
           SKILLS_3, // Energy Weapons
           SKILLS_4, // Unarmed
           SKILLS_5, // Melee Weapons
           SKILLS_6, // Throwing
           SKILLS_7, // First Aid
           SKILLS_8, // Doctor
           SKILLS_9, // Sneak
           SKILLS_10, // Lockpick
           SKILLS_11, // Steal
           SKILLS_12, // Traps
           SKILLS_13, // Science
           SKILLS_14, // Repair
           SKILLS_15, // Speech
           SKILLS_16, // Barter
           SKILLS_17, // Gambling
           SKILLS_18  // Outdoorsman
    };
    enum { SKILLS_SMALL_GUNS = 0,
           SKILLS_BIG_GUNS,
           SKILLS_ENERGY_WEAPONS,
           SKILLS_UNARMED,
           SKILLS_MELEE_WEAPONS,
           SKILLS_THROWING,
           SKILLS_FIRST_AID,
           SKILLS_DOCTOR,
           SKILLS_SNEAK,
           SKILLS_LOCKPICK,
           SKILLS_STEAL,
           SKILLS_TRAPS,
           SKILLS_SCIENCE,
           SKILLS_REPAIR,
           SKILLS_SPEECH,
           SKILLS_BARTER,
           SKILLS_GAMBLING,
           SKILLS_OUTDOORSMAN
    };
    
    enum { DAMAGE_NORMAL = 0,
           DAMAGE_LASER,
           DAMAGE_FIRE,
           DAMAGE_PLASMA,
           DAMAGE_ELECTRICAL,
           DAMAGE_EMP,
           DAMAGE_EXPLOSIVE
    };
    
    GcdFileType(DatFileEntry* datFileEntry);
    GcdFileType(std::ifstream* stream);
    ~GcdFileType();

    void setStat(unsigned int number, unsigned int value);
    unsigned int stat(unsigned int number);
    
    void setStatBonus(unsigned int number, unsigned int value);
    unsigned int statBonus(unsigned int number);

    void setSkill(unsigned int number, unsigned int value);
    unsigned int skill(unsigned int number);
    
    void setDamage(unsigned int type, unsigned int value);
    unsigned int damage(unsigned int type);
    
    void setDamageBonus(unsigned int type, unsigned int value);
    unsigned int damageBonus(unsigned int type);
    
    void setResistance(unsigned int type, unsigned int value);
    unsigned int resistance(unsigned int type);
    
    void setResistanceBonus(unsigned int type, unsigned int value);
    unsigned int resistanceBonus(unsigned int type);
    
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

    void setRadiationResistance(unsigned int radiationResistance);
    unsigned int radiationResistance();

    void setPoisonResistance(unsigned int poisonResistance);
    unsigned int poisonResistance();

    void setAge(unsigned int age);
    unsigned int age();

    void setGender(unsigned int gender);
    unsigned int gender();

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

    void setRadiationResistanceBonus(unsigned int radiationResistanceBonus);
    unsigned int radiationResistanceBonus();

    void setPoisonResistanceBonus(unsigned int poisonResistanceBonus);
    unsigned int poisonResistanceBonus();

    void setAgeBonus(unsigned int ageBonus);
    unsigned int ageBonus();

    void setGenderBonus(unsigned int genderBonus);
    unsigned int genderBonus();

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
