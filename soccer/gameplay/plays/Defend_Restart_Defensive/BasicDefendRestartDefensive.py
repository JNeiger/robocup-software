import main
import robocup
import behavior
import constants
import enum

import standard_play
import tactics.positions.submissive_goalie as submissive_goalie
import tactics.positions.submissive_defender as submissive_defender
import evaluation.opponent as eval_opp
import tactics.positions.wing_defender as wing_defender
import skills.mark as mark
import tactics.defense
import situational_play_selection


## Play that uses submissive defenders to defend
#  an attack close to our goal.
#
#  By default, we will use standard defense (two submissive
#  defenders, one goalie) and additional marking robots. 
#  
class BasicDefendRestartDefensive(standard_play.StandardPlay):

    _situationList = [
        situational_play_selection.SituationalPlaySelector.Situation.DEFEND_RESTART_DEFENSIVE
    ] # yapf: disable


    def __init__(self, num_defenders=2):
        super().__init__(continuous=True)

        self.num_defenders = num_defenders

        self.add_transition(behavior.Behavior.State.start,
                            behavior.Behavior.State.running, lambda: True,
                            'Immediately')

        for i in range(num_defenders):
            self.add_subbehavior(mark.Mark(), 'mark' + str(i), required=False)

        # Keep track of which robots are currently being defended
        self.defended = {}
        for i in range(len(main.their_robots())):
            self.defended[i] = False

    def execute_running(self):
        for i in range(len(main.their_robots())):
            if not eval_opp.is_marked(main.their_robots()[i].pos):
                self.defended[i] = False


        # mark highest threat robot
        for i in range(self.num_defenders):
            mark_bhvr = self.subbehavior_with_name('mark' + str(i))

            threat_found = False            
            for threat_pt, _, _ in eval_opp.get_threat_list([mark_bhvr]):
                print(threat_pt)
                closest_opp = eval_opp.get_closest_opponent(threat_pt)
                if not threat_found and (closest_opp.pos - main.ball().pos).mag() > constants.Field.CenterRadius + constants.Robot.Radius * 2:
                    print((closest_opp.pos - main.ball().pos).mag())
                    # print(constants.Field.CenterRadius)
                    mark_bhvr.mark_robot = closest_opp
                    threat_found = True
