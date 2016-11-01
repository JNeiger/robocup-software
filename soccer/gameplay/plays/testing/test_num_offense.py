import robocup
import constants
import play
import enum
import behavior
import evaluation.opposing_team
import main


class TestNumOnOffense(play.Play):
    class State(enum.Enum):
        idle = 0

    def __init__(self):
        super().__init__(continuous=True)

        self.add_state(TestNumOnOffense.State.idle,
                       behavior.Behavior.State.running)

        self.add_transition(behavior.Behavior.State.start, self.State.idle,
                            lambda: True, 'immediately')

    def execute_idle(self):
        num = evaluation.opposing_team.eval_num_on_offense()
        print(num)
