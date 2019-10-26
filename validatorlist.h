/***************************************************************************
 * Copyright (C) 2014 by Renaud Guezennec                                   *
 * http://www.rolisteam.org/contact                      *
 *                                                                          *
 *  This file is part of DiceParser                                         *
 *                                                                          *
 * DiceParser is free software; you can redistribute it and/or modify       *
 * it under the terms of the GNU General Public License as published by     *
 * the Free Software Foundation; either version 2 of the License, or        *
 * (at your option) any later version.                                      *
 *                                                                          *
 * This program is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             *
 * GNU General Public License for more details.                             *
 *                                                                          *
 * You should have received a copy of the GNU General Public License        *
 * along with this program; if not, write to the                            *
 * Free Software Foundation, Inc.,                                          *
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.                 *
 ***************************************************************************/
#ifndef COMPOSITEVALIDATOR_H
#define COMPOSITEVALIDATOR_H

#include <QList>
#include <QString>
#include <QVector>
#include <Qt>

#include "diceparserhelper.h"
#include <functional>

class Validator;
class Die;
class Result;

struct ValidatorResult {
    std::vector<Die*> m_validDice;
    bool m_allTrue;

    friend bool operator>(const ValidatorResult& a, const ValidatorResult& b) {
        if(a.m_validDice.size() > b.m_validDice.size())
            return true;
        if(a.m_validDice.size() == b.m_validDice.size())
        {
            if(!a.m_allTrue && b.m_allTrue)
                return true;
            else
                return false;
        }
        return false;
    }
};
/**
 * @brief The BooleanCondition class is a Validator class checking validity from logic expression.
 * It manages many operators (see : @ref LogicOperator).
 */
class ValidatorList
{
public:
    enum LogicOperation
    {
        OR,
        EXCLUSIVE_OR,
        AND,
        NONE
    };

    ValidatorList();
    virtual ~ValidatorList();

    virtual qint64 hasValid(Die* b, bool recursive, bool unhighlight= false) const;

    void setOperationList(const QVector<LogicOperation>& m);
    void setValidators(const QList<Validator*>& valids);

    QString toString();

    virtual Dice::CONDITION_STATE isValidRangeSize(const std::pair<qint64, qint64>& range) const;

    virtual ValidatorList* getCopy() const;

    void validResult(Result* result, bool recursive, bool unlight, std::function<void(Die*)> functor) const;

private:
    QVector<LogicOperation> m_operators;
    QList<Validator*> m_validatorList;
};

#endif // BOOLEANCONDITION_H
