import robocup
import constants
import play
import enum
import behavior
import evaluation
import main


class test_num_offense(play.Play):
    class State(enum.Enum):
        idle = 0

    def __init__(self):
        super().__init__(continuous=True)

        # Register the states you defined using 'add_state'.
        # eg: self.add_state(WhichHalf.State.<???>,
        #                    behavior.Behavior.State.running)
        # ----------------------------------------------------
        self.add_state(test_num_offense.State.idle,
                            behavior.Behavior.State.running)
        

        # Add your state transitions using 'add_transition'.
        # eg: self.add_transition(behavior.Behavior.State.start,
        #                         self.State.<???>, lambda: True,
        #                         'immediately')
        # eg: self.add_transition(self.State.<???>, self.State.<???>,
        #                         lambda: <???>,
        #                         'state change message')
        # ------------------------------------------------------------
        self.add_transition(behavior.Behavior.State.start,
                                 self.State.idle, lambda: True,
                                 'immediately')

    # Define your own 'on_enter' and 'execute' functions here.
    # eg: def on_enter_<???>(self):
    #         print('Something?')
    # eg: def execute_<???>(self):
    #         print('Something?')
    # ---------------------------------------------------------
    def execute_idle(self):
             #num = evaluation.opposing_team.eval_num_on_offense()
             num = evaluation.ball.possession()
             print(num)
