import constants
import math
import robocup
import main


## Finds the number of bots that are on the opposing team's offense based on their proximity to the ball and their location on the field
# @return a value from zero to 6 that estimates the number of robots on the opposing teams offense
def eval_num_on_offense():
    ball_pos = main.ball().pos
    ball_to_goal_dist = (
        ball_pos - robocup.Point(0, constants.Field.Length)).mag()
    max_bot_to_goal_dist = (robocup.Point(constants.Field.Width / 2,
                                          constants.Field.Length)).mag()

    num_offense = 0

    for bot in main.their_robots():
        if bot.visible:
            # (1 - Bot_to_ball / ball_to_goal)^2
            ball_scale = (bot.pos - ball_pos).mag() / ball_to_goal_dist
            ball_scale = pow(1 - ball_scale, 2)

            # (bot_to_goal / max_bot_to_goal)^2
            bot_to_goal_dist = (
                bot.pos - robocup.Point(0, constants.Field.Length)).mag()
            pos_scale = pow((bot_to_goal_dist / max_bot_to_goal_dist), 3)

            coeff = .40
            chance_on_offense = coeff * ball_scale + (1 - coeff) * pos_scale

            cutoff = .1
            if chance_on_offense > cutoff:
                num_offense += 1

    return num_offense
