#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>
#include <Geode/modify/GameLevelManager.hpp>

using namespace geode::prelude;

std::string colorIDToName(int id) {
    switch (id) {
        case 1000: return "BG";
        case 1001: return "G1";
        case 1002: return "L";
        case 1003: return "3DL";
        case 1004: return "Obj";
        case 1005: return "P1";
        case 1006: return "P2";
        case 1007: return "LBG";
        case 1008: return "Unknown";
        case 1009: return "G2";
        case 1010: return "Black";
        case 1011: return "White";
        case 1012: return "Lighter";
        case 1013: return "MG";
        case 1014: return "MG2";
        default: return std::to_string(id);
    }
}

class $modify(MOIEditorUI, EditorUI) {
    void updateObjectInfoLabel() {
        EditorUI::updateObjectInfoLabel();
        std::stringstream ss;
        ss << m_objectInfoLabel->getString();
        if (m_selectedObject != nullptr) {
            if (Mod::get()->getSettingValue<bool>("show-object-id")) ss << "ID: " << m_selectedObject->m_objectID << "\n";
            if (Mod::get()->getSettingValue<bool>("show-object-position"))
                ss << "Position: " << m_selectedObject->getPositionX() << ", " << m_selectedObject->getPositionY() - 90.0f << "\n";
            auto rotation = m_selectedObject->getRotation();
            if (Mod::get()->getSettingValue<bool>("show-object-rotation") && rotation != 0.0f) ss << "Rotation: " << rotation << "\n";
            auto scaleX = m_selectedObject->getScaleX();
            auto scaleY = m_selectedObject->getScaleY();
            if (Mod::get()->getSettingValue<bool>("show-object-scale") && (scaleX != 1.0f || scaleY != 1.0f))
                ss << "Scale: " << scaleX << ", " << scaleY << "\n";
            auto baseColor = m_selectedObject->m_baseColor;
            auto detailColor = m_selectedObject->m_detailColor;
            if (Mod::get()->getSettingValue<bool>("show-object-base-color") && baseColor != nullptr) {
                ccHSVValue hsv = baseColor->m_hsv;
                if (hsv.h != 0.0f || hsv.s != 1.0f || hsv.v != 1.0f || hsv.absoluteSaturation != 0 || hsv.absoluteBrightness != 0) {
                    ss << "HSV" << (detailColor != nullptr ? " 1" : "") << ": " << hsv.h << ", "
                        << (hsv.absoluteSaturation != 0 && hsv.s >= 0 ? "+" : "") << hsv.s << ", "
                        << (hsv.absoluteBrightness != 0 && hsv.v >= 0 ? "+" : "") << hsv.v << "\n";
                }
            }
            if (Mod::get()->getSettingValue<bool>("show-object-detail-color") && detailColor != nullptr) {
                ccHSVValue hsv = detailColor->m_hsv;
                if (hsv.h != 0.0f || hsv.s != 1.0f || hsv.v != 1.0f || hsv.absoluteSaturation != 0 || hsv.absoluteBrightness != 0) {
                    ss << "HSV" << (baseColor != nullptr ? " 2" : "") << ": " << hsv.h << ", "
                        << (hsv.absoluteSaturation != 0 && hsv.s >= 0 ? "+" : "") << hsv.s << ", "
                        << (hsv.absoluteBrightness != 0 && hsv.v >= 0 ? "+" : "") << hsv.v << "\n";
                }
            }
        }

        m_objectInfoLabel->setString(ss.str().c_str());
    }
};