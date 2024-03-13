#include <Geode/Geode.hpp>
#include <Geode/modify/EditorUI.hpp>

using namespace geode::prelude;

class $modify(MOIEditorUI, EditorUI) {
    void updateObjectInfoLabel() {
        EditorUI::updateObjectInfoLabel();
        std::stringstream ss;
        ss << m_unk204->getString();
        if (m_selectedObject != nullptr) {
            if (Mod::get()->getSettingValue<bool>("show-object-id")) ss << "ID: " << m_selectedObject->m_objectID << "\n";
            if (Mod::get()->getSettingValue<bool>("show-object-position"))
                ss << "Position: " << m_selectedObject->getPositionX() << ", " << m_selectedObject->getPositionY() - 90.0f << "\n";
            if (Mod::get()->getSettingValue<bool>("show-object-rotation")) ss << "Rotation: " << m_selectedObject->getRotation() << "\n";
            if (Mod::get()->getSettingValue<bool>("show-object-scale")) ss << "Scale: " << m_selectedObject->getScaleX() << ", " << m_selectedObject->getScaleY() << "\n";
        }

        m_unk204->setString(ss.str().c_str());
    }
};
