// Copyright (c) 2011-2020 The future Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef future_QT_futureADDRESSVALIDATOR_H
#define future_QT_futureADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class futureAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit futureAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

/** future address widget validator, checks for a valid future address.
 */
class futureAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit futureAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const override;
};

#endif // future_QT_futureADDRESSVALIDATOR_H
