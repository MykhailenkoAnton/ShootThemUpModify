#pragma once

class AnimUtils
{
public:
    template <typename T>
    static T* FindNotifyByClass(UAnimSequenceBase* Animation)
    {
        if (!Animation) return nullptr;

        const auto NotifiesEvents = Animation->Notifies;
        for (auto NotifiyEvent : NotifiesEvents)
        {
            auto AnimNotify = Cast<T>(NotifiyEvent.Notify);
            if (AnimNotify)
            {
                return AnimNotify;
            }
        }
        return nullptr;
    }
};

