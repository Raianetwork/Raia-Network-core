// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Copyright (c) 2017-2019 The Raven Core developers
// Copyright (c) 2020-2021 The RAIA Network developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RAIANETWORK_SUPPORT_CLEANSE_H
#define RAIANETWORK_SUPPORT_CLEANSE_H

#include <stdlib.h>

// Attempt to overwrite data in the specified memory span.
void memory_cleanse(void *ptr, size_t len);

#endif // RAIANETWORK_SUPPORT_CLEANSE_H
