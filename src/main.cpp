#include <Geode/Geode.hpp>

using namespace geode::prelude;

#include <Geode/modify/EditorUI.hpp>
class $modify(MOIEditorUI, EditorUI) {
    struct Fields {
        bool m_showObjectID;
        bool m_showObjectPosition;
        bool m_showObjectRotation;
        bool m_showObjectScale;
        bool m_showObjectBaseColor;
        bool m_showObjectDetailColor;
        bool m_showObjectType;
        bool m_showObjectAddress;
    };

    bool init(LevelEditorLayer* lel) {
        if (!EditorUI::init(lel)) return false;

        auto mod = Mod::get();
        auto f = m_fields.self();
        f->m_showObjectID = mod->getSettingValue<bool>("show-object-id");
        f->m_showObjectPosition = mod->getSettingValue<bool>("show-object-position");
        f->m_showObjectRotation = mod->getSettingValue<bool>("show-object-rotation");
        f->m_showObjectScale = mod->getSettingValue<bool>("show-object-scale");
        f->m_showObjectBaseColor = mod->getSettingValue<bool>("show-object-base-color");
        f->m_showObjectDetailColor = mod->getSettingValue<bool>("show-object-detail-color");
        f->m_showObjectType = mod->getSettingValue<bool>("show-object-type");
        f->m_showObjectAddress = mod->getSettingValue<bool>("show-object-address");

        return true;
    }

    void updateObjectInfoLabel() {
        EditorUI::updateObjectInfoLabel();

        if (GameManager::sharedState()->getGameVariable("0041") && m_selectedObject) {
            std::stringstream ss;
            ss << m_objectInfoLabel->getString();
            auto f = m_fields.self();

            if (f->m_showObjectID) ss << "ID: " << m_selectedObject->m_objectID << "\n";

            if (f->m_showObjectPosition) ss << "Position: " << m_selectedObject->getPositionX() << ", " << m_selectedObject->getPositionY() - 90.0f << "\n";

            auto rotationX = m_selectedObject->getRotationX();
            auto rotationY = m_selectedObject->getRotationY();
            if (f->m_showObjectRotation && (rotationX != 0.0f || rotationY != 0.0f)) {
                ss << "Rotation: " << rotationX;
                if (rotationX != rotationY) ss << ", " << rotationY;
                ss << "\n";
            }

            auto scaleX = m_selectedObject->getScaleX();
            auto scaleY = m_selectedObject->getScaleY();
            if (f->m_showObjectScale && (scaleX != 1.0f || scaleY != 1.0f)) {
                ss << "Scale: " << scaleX;
                if (scaleX != scaleY) ss << ", " << scaleY;
                ss << "\n";
            }

            auto baseColor = m_selectedObject->m_baseColor;
            auto detailColor = m_selectedObject->m_detailColor;
            if (f->m_showObjectBaseColor && baseColor) {
                auto hsv = baseColor->m_hsv;
                if (hsv.h != 0.0f || hsv.s != 1.0f || hsv.v != 1.0f || hsv.absoluteSaturation || hsv.absoluteBrightness) {
                    ss << "HSV" << (detailColor ? " 1" : "") << ": " << hsv.h << ", "
                        << (hsv.absoluteSaturation && hsv.s >= 0 ? "+" : "") << hsv.s << ", "
                        << (hsv.absoluteBrightness && hsv.v >= 0 ? "+" : "") << hsv.v << "\n";
                }
            }
            if (f->m_showObjectDetailColor && detailColor) {
                auto hsv = detailColor->m_hsv;
                if (hsv.h != 0.0f || hsv.s != 1.0f || hsv.v != 1.0f || hsv.absoluteSaturation || hsv.absoluteBrightness) {
                    ss << "HSV" << (baseColor ? " 2" : "") << ": " << hsv.h << ", "
                        << (hsv.absoluteSaturation && hsv.s >= 0 ? "+" : "") << hsv.s << ", "
                        << (hsv.absoluteBrightness && hsv.v >= 0 ? "+" : "") << hsv.v << "\n";
                }
            }

            if (f->m_showObjectType) {
                ss << "Type: ";
                switch (m_selectedObject->m_objectType) {
                    case GameObjectType::Solid: ss << "Solid"; break;
                    case GameObjectType::Hazard: ss << "Hazard"; break;
                    case GameObjectType::InverseGravityPortal: ss << "Inverse Gravity Portal"; break;
                    case GameObjectType::NormalGravityPortal: ss << "Normal Gravity Portal"; break;
                    case GameObjectType::ShipPortal: ss << "Ship Portal"; break;
                    case GameObjectType::CubePortal: ss << "Cube Portal"; break;
                    case GameObjectType::Decoration: ss << "Decoration"; break;
                    case GameObjectType::YellowJumpPad: ss << "Yellow Jump Pad"; break;
                    case GameObjectType::PinkJumpPad: ss << "Pink Jump Pad"; break;
                    case GameObjectType::GravityPad: ss << "Gravity Pad"; break;
                    case GameObjectType::YellowJumpRing: ss << "Yellow Jump Ring"; break;
                    case GameObjectType::PinkJumpRing: ss << "Pink Jump Ring"; break;
                    case GameObjectType::GravityRing: ss << "Gravity Ring"; break;
                    case GameObjectType::InverseMirrorPortal: ss << "Inverse Mirror Portal"; break;
                    case GameObjectType::NormalMirrorPortal: ss << "Normal Mirror Portal"; break;
                    case GameObjectType::BallPortal: ss << "Ball Portal"; break;
                    case GameObjectType::RegularSizePortal: ss << "Regular Size Portal"; break;
                    case GameObjectType::MiniSizePortal: ss << "Mini Size Portal"; break;
                    case GameObjectType::UfoPortal: ss << "Ufo Portal"; break;
                    case GameObjectType::Modifier: ss << "Modifier"; break;
                    case GameObjectType::Breakable: ss << "Breakable"; break;
                    case GameObjectType::SecretCoin: ss << "Secret Coin"; break;
                    case GameObjectType::DualPortal: ss << "Dual Portal"; break;
                    case GameObjectType::SoloPortal: ss << "Solo Portal"; break;
                    case GameObjectType::Slope: ss << "Slope"; break;
                    case GameObjectType::WavePortal: ss << "Wave Portal"; break;
                    case GameObjectType::RobotPortal: ss << "Robot Portal"; break;
                    case GameObjectType::TeleportPortal: ss << "Teleport Portal"; break;
                    case GameObjectType::GreenRing: ss << "Green Ring"; break;
                    case GameObjectType::Collectible: ss << "Collectible"; break;
                    case GameObjectType::UserCoin: ss << "User Coin"; break;
                    case GameObjectType::DropRing: ss << "Drop Ring"; break;
                    case GameObjectType::SpiderPortal: ss << "Spider Portal"; break;
                    case GameObjectType::RedJumpPad: ss << "Red Jump Pad"; break;
                    case GameObjectType::RedJumpRing: ss << "Red Jump Ring"; break;
                    case GameObjectType::CustomRing: ss << "Custom Ring"; break;
                    case GameObjectType::DashRing: ss << "Dash Ring"; break;
                    case GameObjectType::GravityDashRing: ss << "Gravity Dash Ring"; break;
                    case GameObjectType::CollisionObject: ss << "Collision Object"; break;
                    case GameObjectType::Special: ss << "Special"; break;
                    case GameObjectType::SwingPortal: ss << "Swing Portal"; break;
                    case GameObjectType::GravityTogglePortal: ss << "Gravity Toggle Portal"; break;
                    case GameObjectType::SpiderOrb: ss << "Spider Orb"; break;
                    case GameObjectType::SpiderPad: ss << "Spider Pad"; break;
                    case GameObjectType::EnterEffectObject: ss << "Enter Effect Object"; break;
                    case GameObjectType::TeleportOrb: ss << "Teleport Orb"; break;
                    case GameObjectType::AnimatedHazard: ss << "Animated Hazard"; break;
                    default: ss << "Unknown"; break;
                }
                ss << " (" << (int)m_selectedObject->m_objectType << ")\n";
            }

            if (f->m_showObjectAddress) ss << "Address: " << std::hex << fmt::to_string(fmt::ptr(m_selectedObject)) << std::dec << "\n";

            m_objectInfoLabel->setString(ss.str().c_str());
        }
    }
};
