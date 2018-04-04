/*
 *     Copyright (C) 2006-2018 Sumandeep Banerjee
 * 
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* 
 * File:   main.h
 * Author: sumandeep
 * Email:  sumandeep.banerjee@gmail.com
 *
 * Created on 4 April, 2018, 6:05 AM
 */

#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

int main_mfcc (int argc, char * argv []);
int main_batch (int argc, char * argv []);
int main_cluster (int argc, char * argv []);
int main_query (int argc, char * argv []);

#ifdef __cplusplus
}
#endif

#endif /* MAIN_H */

