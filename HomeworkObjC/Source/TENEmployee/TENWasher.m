//
//  TENWasher.m
//  HomeworkC
//
//  Created by 444ten on 4/16/15.
//  Copyright (c) 2015 444ten. All rights reserved.
//

#import "TENWasher.h"

#import "TENCar.h"

@implementation TENWasher

#pragma mark -
#pragma mark Public

- (void)washCar:(TENCar *)car {
    usleep(1000 * arc4random_uniform(10));
    NSLog(@"%@ clear %@", self.name, car.model);
}

#pragma mark -
#pragma mark Overload

- (void)finalizeWorkWithObject:(id)object {
    
}

- (void)processObject:(id)object {
    [self washCar:object];
    [self takeMoney:[object giveMoney]];
}

@end
