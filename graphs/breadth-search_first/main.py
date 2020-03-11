import rospy
from nav_msgs.msg import OccupancyGrid
from std_msgs.msg import Int16MultiArray

BFS:
    def __init__(self):
        rospy.init_node('BFS_path_searcher')

        self.publisher = rospy.Publisher("/map")
        rospy.spin()


    def run():
        
if __name__ == '__main__':
    BFS()
