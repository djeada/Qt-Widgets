from PyQt6.QtCore import QLineF, QPointF
from PyQt6.QtGui import QPen, QColor
from PyQt6.QtWidgets import QGraphicsScene

from movable_image import MovableImage


class BorderedScene(QGraphicsScene):
    def __init__(self, border_rect, num_balls, parent=None):
        super().__init__(parent)
        self.setSceneRect(border_rect)
        self.drawSceneBorder()

        for _ in range(num_balls):
            self.addItem(MovableImage(self.sceneRect(), self))

    def drawSceneBorder(self):
        top_line = QLineF(self.sceneRect().topLeft(), self.sceneRect().topRight())
        left_line = QLineF(self.sceneRect().topLeft(), self.sceneRect().bottomLeft())
        right_line = QLineF(self.sceneRect().topRight(), self.sceneRect().bottomRight())
        bottom_line = QLineF(self.sceneRect().bottomLeft(), self.sceneRect().bottomRight())

        pen = QPen(QColor('red'))

        self.addLine(top_line, pen)
        self.addLine(left_line, pen)
        self.addLine(right_line, pen)
        self.addLine(bottom_line, pen)

    def advance(self):
        QGraphicsScene.advance(self)

        objects_to_check = {}

        # fill with all items that are QMovableImage
        for item in self.items():
            # use dynamic cast to check if item is MovableImage
            if isinstance(item, MovableImage):
                movable_image = item
                objects_to_check[movable_image] = True

        # check for collisions
        for compared_object, value in objects_to_check.items():
            if not value:
                continue

            objects_to_check[compared_object] = False

            for other_item in self.collidingItems(compared_object):

                if other_item is None or not isinstance(other_item, MovableImage) or not objects_to_check[other_item]:
                    continue
                  
                # swap speed directions
                other_item_speed_dir = other_item.speed_direction()
                compared_object_speed_dir = compared_object.speed_direction()
                compared_object.speed = QPointF(abs(compared_object.speed.x())*other_item_speed_dir.x(), abs(compared_object.speed.y())*other_item_speed_dir.y())
                other_item.speed = QPointF(abs(other_item.speed.x())*compared_object_speed_dir.x(), abs(other_item.speed.y())*compared_object_speed_dir.y())

                # move the objects so they don't overlap
                compared_object.moveBy(compared_object.speed.x(), compared_object.speed.y())
                other_item.moveBy(other_item.speed.x(), other_item.speed.y())
                objects_to_check[other_item] = False
