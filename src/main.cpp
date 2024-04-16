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
            if (Mod::get()->getSettingValue<bool>("show-object-rotation")) ss << "Rotation: " << m_selectedObject->getRotation() << "\n";
            if (Mod::get()->getSettingValue<bool>("show-object-scale")) ss << "Scale: " << m_selectedObject->getScaleX() << ", " << m_selectedObject->getScaleY() << "\n";
            if (Mod::get()->getSettingValue<bool>("show-object-base-color") && m_selectedObject->m_baseColor != nullptr) {
                auto baseColor = m_selectedObject->m_baseColor;
                auto colorID = colorIDToName(baseColor->m_colorID != 0 ? baseColor->m_colorID : baseColor->m_defaultColorID);
                ss << "Base Color: " << colorID;
                ccHSVValue hsv = baseColor->m_hsv;
                if (hsv.h != 0.0f || hsv.s != 1.0f || hsv.v != 1.0f || hsv.absoluteSaturation != 0 || hsv.absoluteBrightness != 0) {
                    ss << " + HSV(" << hsv.h << ", "
                        << (hsv.absoluteSaturation != 0 && hsv.s >= 0 ? "+" : "") << hsv.s << ", "
                        << (hsv.absoluteBrightness != 0 && hsv.v >= 0 ? "+" : "") << hsv.v << ")";
                }
                ss << "\n";
            }
            if (Mod::get()->getSettingValue<bool>("show-object-detail-color") && m_selectedObject->m_detailColor != nullptr) {
                auto detailColor = m_selectedObject->m_detailColor;
                auto colorID = colorIDToName(detailColor->m_colorID != 0 ? detailColor->m_colorID : detailColor->m_defaultColorID);
                ss << "Detail Color: " << colorID;
                ccHSVValue hsv = detailColor->m_hsv;
                if (hsv.h != 0.0f || hsv.s != 1.0f || hsv.v != 1.0f || hsv.absoluteSaturation != 0 || hsv.absoluteBrightness != 0) {
                    ss << " + HSV(" << hsv.h << ", "
                        << (hsv.absoluteSaturation != 0 && hsv.s >= 0 ? "+" : "") << hsv.s << ", "
                        << (hsv.absoluteBrightness != 0 && hsv.v >= 0 ? "+" : "") << hsv.v << ")";
                }
                ss << "\n";
            }
        }

        m_objectInfoLabel->setString(ss.str().c_str());
    }
};