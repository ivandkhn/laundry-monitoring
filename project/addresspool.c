/*
    Copyright (c) 2022 Group 5, SDN Lab

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, version 2.0 of the License.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "addresspool.h"
#include "stdio.h"

/**
 * Try to add an address to the pool. Nothing happens if the address
 * already exists,
 *
 * @param pool A pointer to the addresspool structure.
 * @param addr New address to add.
 */
void poolAdd(addresspool_t *pool, linkaddr_t addr) {
    printf("poolAdd for addr %d.%d\n", addr.u8[0], addr.u8[1]);
    for (int i = 0; i < pool->validAddresses; ++i) {
        if (linkaddr_cmp(&pool->addresses[i], &addr) != 0) {
            // This address already exists in pool and valid.
            printf("address already exists\n");
            return;
        }
    }
    pool->validAddresses++;
    pool->addresses[pool->validAddresses-1] = addr;
    pool->currentAddress = pool->validAddresses-1;
    printf("poolAdd success, validAddresses=%d\n", pool->validAddresses);
}

/**
 * Remove the address from the pool.
 *
 * @param pool A pointer to the addresspool structure.
 * @param addr An address for deletion. Note that this address is assumed
 * to be present in a pool.
 */
void poolRemove(addresspool_t *pool, linkaddr_t addr) {
    printf("poolRemove for addr %d.%d\n", addr.u8[0], addr.u8[1]);
    uint8_t idx = 0;
    while (linkaddr_cmp(&pool->addresses[idx], &addr) == 0) {
        idx++;
    }
    printf("poolRemove: removing position %d\n", idx);
    while (idx < pool->validAddresses-1) {
        pool->addresses[idx] = pool->addresses[idx+1];
        idx++;
    }
    pool->validAddresses--;
    printf("poolRemove: [%d] valid addresses left\n", pool->validAddresses);
}

/**
 * Get a new address from the pool of valid addresses
 * and cycle the internal index.
 *
 * @param pool A pointer to the addresspool structure.
 * @return Valid mote address.
 */
linkaddr_t poolGet(addresspool_t *pool) {
    linkaddr_t addr = pool->addresses[pool->currentAddress];
    printf("poolGet: currentAddressIdx=%d, address = %d.%d\n",
           pool->currentAddress, addr.u8[0], addr.u8[1]);
    pool->currentAddress++;
    if (pool->currentAddress >= pool->validAddresses) {
        pool->currentAddress = 0;
    }
    return addr;
}
