import rospy
import actionlib

from control_msgs.msg import FollowJointTrajectoryAction, FollowJointTrajectoryGoal
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint

class TrajectoryDemo():
    def __init__(self):
        rospy.init_node('trajectory_name')

        # 是否要回到初始化的位置
        reset = rospy.get_param('~reset', False)

        #机械臂中joint的命名
        arm_joint = ['joint1','joint2','joint3','joint4','joint5','joint6']
        if reset:
            #如果要回到初始化位置，则将目标位置设置为初始化的六轴角度
            arm_goal = [0 ,0 ,0 ,0 ,0 ,0]
        else:
            arm_goal = [-0.3 ,-1.0 ,0.5 ,0.8 ,1.0 ,-0.7]
        rospy.loginfo('Waiting for arm trajectory controller.....')
        arm_client = actionlib.SimpleActionClient('arm_controller/follow_joint_trajectory', FollowJointTrajectoryAction)
        rospy.loginfo('connected...')

        #使用设定的目标为值创建一条轨迹数据
        arm_trajectory = JointTrajectory()
        arm_trajectory.joint_names = arm_joint
        arm_trajectory.points.append(JointTrajectoryPoint())
        arm_trajectory.points[0].positions = arm_goal
        arm_trajectory.points[0].velocities = [0 for i in arm_joint]
        arm_trajectory.points[0].accelerations = [0 for i in arm_joint]
        arm_trajectory.points[0].time_from_start = rospy.Duration(3.0)

        # 轨迹目标的空对象
        arm_goal = FollowJointTrajectoryGoal()
        arm_goal.trajectory = arm_trajectory
        arm_goal.goal_time_tolerance = rospy.Duration(0.0)

        arm_client.send_goal(arm_goal)

        #  等待机械臂运动结束 
        arm_client.wait_for_result(rospy.Duration(5.0))

        rospy.loginfo('...done')

if __name__ == '__main__':
    try:
        TrajectoryDemo()
    except rospy.ROSInterruptException:
        pass

