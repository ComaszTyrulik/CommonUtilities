#pragma once
#include "Common/Types.h"
#include "Common/Helpers.h"

namespace CT_COMMON_NAMESPACE
{
    /**
     * @brief Template interface for zero arguments factories returning unique instances of the given TypeOfFactory.
     */
    template<typename TypeOfFactory>
    class IUniqueFactory
    {
    public:
        using FactoryType = TypeOfFactory;

    public:
        SCE_IMPLEMENT_ADDITIONAL_CONSTRUCTORS_DELETED(IUniqueFactory);
        IUniqueFactory() = default;
        virtual ~IUniqueFactory() = default;

        virtual UniquePtr<FactoryType> Create() const = 0;
    };

    /**
     * @brief Template interface for single arguments factories returning unique instances of the given TypeOfFactory.
     */
    template<typename TypeOfFactory, typename TypeOfParam>
    class IUniqueFactoryWithParam
    {
    public:
        using FactoryType = TypeOfFactory;
        using ParamType = TypeOfParam;

    public:
        SCE_IMPLEMENT_ADDITIONAL_CONSTRUCTORS_DELETED(IUniqueFactoryWithParam);
        IUniqueFactoryWithParam() = default;
        virtual ~IUniqueFactoryWithParam() = default;

        virtual UniquePtr<FactoryType> Create(ParamType param) const = 0;
    };

    /**
     * @brief Template interface for single arguments factories returning shared instances of the given TypeOfFactory.
     */
    template<typename TypeOfFactory, typename TypeOfParam>
    class ISharedFactoryWithParam
    {
    public:
        using FactoryType = TypeOfFactory;
        using ParamType = TypeOfParam;

    public:
        SCE_IMPLEMENT_ADDITIONAL_CONSTRUCTORS_DELETED(ISharedFactoryWithParam);
        ISharedFactoryWithParam() = default;
        virtual ~ISharedFactoryWithParam() = default;

        virtual SharedPtr<FactoryType> Create(ParamType param) const = 0;
    };

    /**
     * @brief Class template automatically creating implementation of the IUniqueFactory interface template.
     * It provides a convenient way to create instance of the simple unique factory.
     * Given ConcreteType which instance will be created, must be a child of the given InterfaceType. Compile-time error is generated otherwise.
     */
    template<typename InterfaceType, typename ConcreteType>
    class AutomaticInterfaceFactory : public IUniqueFactory<InterfaceType>
    {
        static_assert(std::is_base_of_v<InterfaceType, ConcreteType>, "Provided ConcreteType does not inherit from InterfaceType");

    public:
        std::unique_ptr<InterfaceType> Create() const override
        {
            return std::make_unique<ConcreteType>();
        }
    };
} // namespace CT_COMMON_NAMESPACE
