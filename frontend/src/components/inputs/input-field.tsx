import { ChangeEvent, useEffect, useState } from "react";
import { InputFieldProps } from "../../../types/input-types";
import {
  FormControl,
  FormField,
  FormItem,
  FormLabel,
  FormMessage,
} from "../ui/form";
import { Input } from "../ui/input";

export function InputField({
  label,
  unit,
  name,
  value = 0,
  placeholder = "enter value...",
  isReadOnly = false,
  control,
}: InputFieldProps) {
  const [inputValue, setInputValue] = useState<string>(
    value !== 0 ? value.toString() : ""
  );
  const [isModified, setIsModified] = useState(false);

  useEffect(() => {
    if (value !== 0 || !isModified) {
      setInputValue(value.toString());
    }
  }, [value, isModified]);
  return (
    <FormField
      control={control}
      name={name}
      render={({ field }) => (
        <FormItem className="w-full">
          <FormLabel>{label}</FormLabel>
          <FormControl>
            <div className="flex items-center gap-2">
              <Input
                placeholder={placeholder}
                type="number"
                step="any"
                readOnly={isReadOnly}
                className={`flex-1 ${
                  isReadOnly ? "bg-blue-50 border-blue-200" : ""
                }`}
                {...field}
                onChange={(e) => {
                  const value = e.target.value;
                  field.onChange(value === "" ? "" : Number(value));
                }}
              />
              {unit && (
                <span className="text-sm text-gray-600 min-w-fit whitespace-nowrap">
                  {unit}
                </span>
              )}
            </div>
          </FormControl>
          <FormMessage />
        </FormItem>
      )}
    />
  );
}
