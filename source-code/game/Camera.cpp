#include "Camera.h"

Camera::Camera(sf::FloatRect bounds)
                        : camera_(std::make_unique<sf::View>(bounds))
                        , bounds_(bounds) {
    camera_->zoom(1);
}

void Camera::zoom(double zoom, int x, int y, sf::RenderWindow* window) {
    const sf::Vector2f beforeCoord{ window->mapPixelToCoords({x, y}) };
    sf::View oldCamera = *camera_.get();
    camera_->zoom(zoom);
    window->setView(*camera_.get());
    const sf::Vector2f afterCoord{ window->mapPixelToCoords({x, y}) };
    const sf::Vector2f offsetCoords{ beforeCoord - afterCoord };
    window->setView(oldCamera);
    if (offsetCoords.x > 0) {
        moveRight(offsetCoords.x);
    } else if (offsetCoords.x < 0) {
        moveLeft(-offsetCoords.x);
    }
    if (offsetCoords.y > 0) {
        moveDown(offsetCoords.y);
    } else if (offsetCoords.y < 0) {
        moveUp(-offsetCoords.y);
    }
}

void Camera::zoomIn(int x, int y, sf::RenderWindow* window) {
    double newZoom = 1 + zoomStep_;
    if (camera_->getSize().x < maxHeight_) {
        zoom(newZoom, x, y, window);
    }
}
void Camera::zoomOut(int x, int y, sf::RenderWindow* window) {
    double newZoom = 1 - zoomStep_;
    if (camera_->getSize().x > minHeight_) {
        zoom(newZoom, x, y, window);
    }
}

void Camera::moveLeft(int offset) {
    int limitedOffset = getLimitedOffset(
            camera_->getCenter().x - bounds_.left,
            offset,
            camera_->getSize().x);
    camera_->move(-limitedOffset, 0);
}

void Camera::moveRight(int offset) {
    int limitedOffset = getLimitedOffset(
            bounds_.left+bounds_.width - camera_->getCenter().x,
            offset,
            camera_->getSize().x);
    camera_->move(limitedOffset, 0);
}

void Camera::moveUp(int offset) {
    int limitedOffset = getLimitedOffset(
            camera_->getCenter().y - offset - bounds_.top,
            offset,
            camera_->getSize().y);
    camera_->move(0, -limitedOffset);
}

void Camera::moveDown(int offset) {
    int limitedOffset = getLimitedOffset(
            bounds_.top+bounds_.height - camera_->getCenter().y,
            offset,
            camera_->getSize().y);
    camera_->move(0, limitedOffset);
}

sf::View *Camera::getView() {
    return camera_.get();
}

int Camera::getMoveStep() const {
    return moveStep_;
}

int Camera::getLimitedOffset(int currentPosition, int offset, int size) {
    int moveLimit = currentPosition - offset - size * moveOutLimitPortion_;
    int limitedOffset = offset;
    if (moveLimit < 0) {
        limitedOffset += moveLimit;
    }
    return limitedOffset;
}
