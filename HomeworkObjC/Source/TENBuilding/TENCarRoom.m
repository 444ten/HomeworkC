//
//  TENCarRoom.m
//  HomeworkC
//
//  Created by 444ten on 4/15/15.
//  Copyright (c) 2015 444ten. All rights reserved.
//

#import "TENCarRoom.h"

#import "TENCar.h"

@interface TENCarRoom ()
@property (nonatomic, retain)   NSMutableArray  *mutableCars;

@end

@implementation TENCarRoom

@dynamic cars;

#pragma mark -
#pragma mark Initializations and Deallocations

- (void)dealloc {
    self.mutableCars = nil;
    
    [super dealloc];
}

- (instancetype)init {
    self = [super init];
    if (self) {
        self.mutableCars = [NSMutableArray array];
    }
    
    return self;
}

#pragma mark -
#pragma mark Accessors

- (NSArray *)cars {
    return [[self.mutableCars copy] autorelease];
}

#pragma mark -
#pragma mark Public

- (void)addCar:(TENCar *)car {
    NSMutableArray *aCars = self.mutableCars;
    
    if (aCars.count < self.carCapacity && ![aCars containsObject:car]) {
        [aCars addObject:car];
    }
}

- (void)removeCar:(TENCar *)car {
    [self.mutableCars removeObject:car];
}

@end
