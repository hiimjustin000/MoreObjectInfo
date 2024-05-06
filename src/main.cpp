#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(MOIEditorUI, EditorUI) {
    void updateObjectInfoLabel() {
        EditorUI::updateObjectInfoLabel();

        std::stringstream ss;
        ss << m_objectInfoLabel->getString();

        if (m_selectedObject) {
            auto mod = Mod::get();

            if (mod->getSettingValue<bool>("show-object-id")) ss << "ID: " << m_selectedObject->m_objectID << "\n";

            if (mod->getSettingValue<bool>("show-object-position"))
                ss << "Position: " << m_selectedObject->getPositionX() << ", " << m_selectedObject->getPositionY() - 90.0f << "\n";

            auto rotation = m_selectedObject->getRotation();
            if (mod->getSettingValue<bool>("show-object-rotation") && rotation != 0.0f) ss << "Rotation: " << rotation << "\n";

            auto scaleX = m_selectedObject->getScaleX();
            auto scaleY = m_selectedObject->getScaleY();
            if (mod->getSettingValue<bool>("show-object-scale") && (scaleX != 1.0f || scaleY != 1.0f))
                ss << "Scale: " << scaleX << ", " << scaleY << "\n";

            auto baseColor = m_selectedObject->m_baseColor;
            auto detailColor = m_selectedObject->m_detailColor;
            if (mod->getSettingValue<bool>("show-object-base-color") && baseColor) {
                ccHSVValue hsv = baseColor->m_hsv;
                if (hsv.h != 0.0f || hsv.s != 1.0f || hsv.v != 1.0f || hsv.absoluteSaturation || hsv.absoluteBrightness) {
                    ss << "HSV" << (detailColor ? " 1" : "") << ": " << hsv.h << ", "
                        << (hsv.absoluteSaturation && hsv.s >= 0 ? "+" : "") << hsv.s << ", "
                        << (hsv.absoluteBrightness && hsv.v >= 0 ? "+" : "") << hsv.v << "\n";
                }
            }
            if (mod->getSettingValue<bool>("show-object-detail-color") && detailColor) {
                ccHSVValue hsv = detailColor->m_hsv;
                if (hsv.h != 0.0f || hsv.s != 1.0f || hsv.v != 1.0f || hsv.absoluteSaturation || hsv.absoluteBrightness) {
                    ss << "HSV" << (baseColor ? " 2" : "") << ": " << hsv.h << ", "
                        << (hsv.absoluteSaturation && hsv.s >= 0 ? "+" : "") << hsv.s << ", "
                        << (hsv.absoluteBrightness && hsv.v >= 0 ? "+" : "") << hsv.v << "\n";
                }
            }

            if (mod->getSettingValue<bool>("show-object-address"))
                ss << "Address: " << std::hex << fmt::to_string(fmt::ptr(m_selectedObject)) << std::dec << "\n";
        }

        m_objectInfoLabel->setString(ss.str().c_str());
    }
};
