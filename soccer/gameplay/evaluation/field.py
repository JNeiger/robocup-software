import main
import robocup
import constants
import math

## Determines how much "space" there is at a pos
#    "Space" is how empty an area of the field is
# @param pos: point to evalute
# @returns Number between 0 and 1 representing the closeness of robots
# The higher the number, the more robots closer to the position
def space_coeff_at_pos(pos, excluded_robots=[]):
    # TODO: Add in velocity prediction

    max_dist = robocup.Point(constants.Field.Width/2, constants.Field.Length).mag()
    total = 0
    sensitivity = 8

    for bot in (main.their_robots()):
        if bot.visible and bot not in excluded_robots:
            u = sensitivity * (bot.pos - pos).mag() / max_dist;

            # Use Triweight kernal function (Force to be positive)
            # Graph looks much like a normal distribution
            total += max((35/32)*pow((1-pow(u,2)), 3), 0)

    return min(total, 1)



## Field Heuristic based on the position of the robot on the field
# Weight inputs are normalized
#
# @param pos: Position to evalute
# @param center: How much to weight being close to the 'center of the field'
# @param dist: How much to weight being close to the opponents goal
# @param angl: How much to weight the angle between the robot and the goal (In turn, how small the goal is)
# @return Returns a number between 0 and 1 representing how good the position is 
def field_pos_coeff_at_pos(pos, center = 0.2, dist = 1, angl = 1):
    # Percent closeness to the center (Line between the two goals is the 'center line')
    centerValue = 1 - math.fabs(pos.x / (constants.Field.Width / 2))
    # Pencent closeness to their goal
    distValue = math.fabs(pos.y / constants.Field.Length) 
    # Angle of pos onto the goal, centerline is 0 degrees
    anglValue = 1  -  math.fabs(math.atan2(pos.x, constants.Field.Length - pos.y) / (math.pi/2)) 

    # Normalize inputs
    total = center + dist + angl

    return (center*centerValue + dist*distValue + angl*anglValue) / total