"use client";

import { AppSidebar } from "@/components/app-sidebar";
import { ModeToggle } from "@/components/toggle-mode-button";
import {
  Form,
  FormControl,
  FormField,
  FormItem,
  FormLabel,
  FormMessage,
} from "@/components/ui/form";
import { Input } from "@/components/ui/input";
import { SidebarProvider, SidebarTrigger } from "@/components/ui/sidebar";
import { useForm } from "react-hook-form";
import { z } from "zod";
import { zodResolver } from "@hookform/resolvers/zod";
import { toast } from "sonner";
import { Button } from "@/components/ui/button";
import { useState } from "react";
import {
  Card,
  CardContent,
  CardDescription,
  CardHeader,
  CardTitle,
} from "@/components/ui/card";
import {
  Select,
  SelectContent,
  SelectItem,
  SelectTrigger,
  SelectValue,
} from "@/components/ui/select";

const FormSchema = z.object({
  i_T: z.number({
    message: "iCt Must be a number or decimal",
  }),
  i_M: z.number({
    message: "iCm Must be a number  or decimal",
  }),
  n_axle: z.number({
    message: "Number of Axle must be a number",
  }),
  n_tm: z.number({
    message: "Number of Traction Motor must be a number",
  }),
  wheelDiameter: z.number({
    message: "Wheel Diameter must be a number",
  }),
  mass_P: z.number({
    message: "Passenger Weight must be a number",
  }),
  gearRatio: z.number({
    message: "Gear Ratio must be a number",
  }),
  load: z.number({
    message: "Load per car must be a number",
  }),
  carLength: z.number({
    message: "Car Length must be a number",
  }),
  loadCondition: z.enum(["AW0", "AW1", "AW2", "AW3", "AW4"], {
    message: "Load Condition must be one of AW0, AW1, AW2, AW3, AW4",
  }),
});

export default function Main() {
  const [isSubmitting, setIsSubmitting] = useState(false);
  const form = useForm<z.infer<typeof FormSchema>>({
    resolver: zodResolver(FormSchema),
    defaultValues: {
      i_T: 1.05,
      i_M: 1.1,
      n_axle: 4,
      n_tm: 24,
      wheelDiameter: 860,
      mass_P: 70,
      gearRatio: 3,
      load: undefined,
      carLength: 20,
      loadCondition: "AW4",
    },
  });

  const inputFormDatas = [
    {
      label: "Inertial Coefficient Trailer",
      unit: "",
      name: "i_T" as keyof z.infer<typeof FormSchema>,
    },
    {
      label: "Inertial Coefficient Motor",
      unit: "",
      name: "i_M" as keyof z.infer<typeof FormSchema>,
    },
    {
      label: "Number of Axle",
      unit: "",
      name: "n_axle" as keyof z.infer<typeof FormSchema>,
    },
    {
      label: "Number of Traction Motor",
      unit: "",
      name: "n_tm" as keyof z.infer<typeof FormSchema>,
    },
    {
      label: "Wheel Diameter",
      unit: "mm",
      name: "wheelDiameter" as keyof z.infer<typeof FormSchema>,
    },
    {
      label: "Passenger Weight",
      unit: "kg",
      name: "mass_P" as keyof z.infer<typeof FormSchema>,
    },
    {
      label: "Gear Ratio",
      unit: "mm",
      name: "gearRatio" as keyof z.infer<typeof FormSchema>,
    },
    {
      label: "Load per Car",
      unit: "ton",
      name: "load" as keyof z.infer<typeof FormSchema>,
    },
    {
      label: "Car Length",
      unit: "m",
      name: "carLength" as keyof z.infer<typeof FormSchema>,
    },
    {
      label: "Load Condition",
      unit: "",
      name: "loadCondition" as keyof z.infer<typeof FormSchema>,
    },
  ];

  const chunkArray = <T,>(array: T[], chunkSize: number): T[][] => {
    const chunks: T[][] = [];
    for (let i = 0; i < array.length; i += chunkSize) {
      chunks.push(array.slice(i, i + chunkSize));
    }
    return chunks;
  };

  const formRows = chunkArray(inputFormDatas, 3);

  const renderFormFields = (fieldData: (typeof inputFormDatas)[0]) => {
    if (fieldData.name === "loadCondition") {
      return (
        <FormField
          key={fieldData.name}
          control={form.control}
          name={fieldData.name}
          render={({ field }) => (
            <FormItem className="w-full">
              <FormLabel>{fieldData.label}</FormLabel>
              <Select onValueChange={field.onChange} defaultValue={field.value}>
                <FormControl className="w-full">
                  <SelectTrigger>
                    <SelectValue placeholder="Pilih AW Condition" />
                  </SelectTrigger>
                </FormControl>
                <SelectContent>
                  <SelectItem value="AW0">AW0</SelectItem>
                  <SelectItem value="AW1">AW1</SelectItem>
                  <SelectItem value="AW2">AW2</SelectItem>
                  <SelectItem value="AW3">AW3</SelectItem>
                  <SelectItem value="AW4">AW4</SelectItem>
                </SelectContent>
              </Select>
              <FormMessage />
            </FormItem>
          )}
        />
      );
    }
  };

  async function onSubmit(data: z.infer<typeof FormSchema>) {
    setIsSubmitting(true);
    try {
      console.log("Form Data:", data);
      toast("Data berhasil disimpan!", {
        description: (
          <pre className="mt-2 w-[320px] rounded-md bg-neutral-950 p-4">
            <code className="text-white">{JSON.stringify(data, null, 2)}</code>
          </pre>
        ),
      });
    } catch (error) {
      toast("Error!", {
        description: "Gagal menyimpan data. Silakan coba lagi.",
      });
    } finally {
      setIsSubmitting(false);
    }
  }
  return (
    <SidebarProvider>
      <div className="absolute top-4 left-4 flex flex-row">
        <AppSidebar />
        <SidebarTrigger size="lg" />
      </div>
      <div className="flex flex-col w-full h-screen justify-center items-center">
        <div className="absolute top-4 right-4">
          <ModeToggle />
        </div>
        <Card className="px-4 py-8 max-w-xl rounded-3xl">
          <CardHeader className="text-center">
            <CardTitle className="text-xl">Train Parameter</CardTitle>
            <CardDescription>Input related to Train and Car</CardDescription>
          </CardHeader>
          <CardContent>
            <Form {...form}>
              <form
                onSubmit={form.handleSubmit(onSubmit)}
                className="space-y-6"
              >
                <div className="flex flex-col gap-6">
                  <div className="grid grid-cols-3 gap-4">
                    {/* <FormField control={form.control} name={} /> */}
                    <FormField
                      control={form.control}
                      name="i_T"
                      render={({ field }) => (
                        <FormItem>
                          <FormLabel>Inertial Coefficient Trailer</FormLabel>
                          <FormControl>
                            <div className="flex flex-row gap-2">
                              <Input placeholder="enter value..." {...field} />{" "}
                              <span className="self-center">mm</span>
                            </div>
                          </FormControl>
                          <FormMessage />
                        </FormItem>
                      )}
                    />

                    <FormField
                      control={form.control}
                      name="i_M"
                      render={({ field }) => (
                        <FormItem className="w-full">
                          <FormLabel>Inertial Coefficient Motor</FormLabel>
                          <FormControl>
                            <div className="flex flex-row gap-2">
                              <Input placeholder="enter value..." {...field} />
                              <span className="self-center">mm</span>
                            </div>
                          </FormControl>
                          <FormMessage />
                        </FormItem>
                      )}
                    />
                    <FormField
                      control={form.control}
                      name="n_axle"
                      render={({ field }) => (
                        <FormItem className="w-full">
                          <FormLabel>Number of Axle</FormLabel>
                          <FormControl>
                            <div className="flex flex-row gap-2">
                              <Input placeholder="Staff muda" {...field} />
                              <span className="self-center">mm</span>
                            </div>
                          </FormControl>
                          <FormMessage />
                        </FormItem>
                      )}
                    />
                  </div>
                  <div className="grid grid-cols-3 gap-4">
                    <FormField
                      control={form.control}
                      name="n_tm"
                      render={({ field }) => (
                        <FormItem className="w-full">
                          <FormLabel>Number of Traction Motor</FormLabel>
                          <FormControl>
                            <div className="flex flex-row gap-2">
                              <Input placeholder="enter value..." {...field} />
                              <span className="self-center">mm</span>
                            </div>
                          </FormControl>
                          <FormMessage />
                        </FormItem>
                      )}
                    />
                    <FormField
                      control={form.control}
                      name="wheelDiameter"
                      render={({ field }) => (
                        <FormItem className="w-full">
                          <FormLabel className="w-16">Wheel Diameter</FormLabel>
                          <FormControl>
                            <div className="flex flex-row gap-2">
                              <Input placeholder="enter value..." {...field} />{" "}
                              <span className="self-center">mm</span>
                            </div>
                          </FormControl>
                          <FormMessage />
                        </FormItem>
                      )}
                    />
                    <FormField
                      control={form.control}
                      name="mass_P"
                      render={({ field }) => (
                        <FormItem className="w-full">
                          <FormLabel>Passenger Weight</FormLabel>
                          <FormControl>
                            <div className="flex flex-row gap-2">
                              <Input placeholder="enter value..." {...field} />
                              <span className="self-center">kg</span>
                            </div>
                          </FormControl>
                          <FormMessage />
                        </FormItem>
                      )}
                    />
                  </div>
                  <div className="grid grid-cols-3 gap-4">
                    <FormField
                      control={form.control}
                      name="gearRatio"
                      render={({ field }) => (
                        <FormItem className="w-full">
                          <FormLabel>Gear Ratio</FormLabel>
                          <FormControl>
                            <div className="flex flex-row gap-2">
                              <Input placeholder="enter value..." {...field} />
                              <span className="self-center">mm</span>
                            </div>
                          </FormControl>
                          <FormMessage />
                        </FormItem>
                      )}
                    />
                    <FormField
                      control={form.control}
                      name="load"
                      render={({ field }) => (
                        <FormItem className="w-full">
                          <FormLabel>Load per Car</FormLabel>
                          <FormControl>
                            <div className="flex flex-row gap-2">
                              <Input placeholder="enter value..." {...field} />
                              <span className="self-center">ton</span>
                            </div>
                          </FormControl>
                          <FormMessage />
                        </FormItem>
                      )}
                    />
                    <FormField
                      control={form.control}
                      name="carLength"
                      render={({ field }) => (
                        <FormItem className="w-full">
                          <FormLabel>Car Length</FormLabel>
                          <FormControl>
                            <div className="flex flex-row gap-2">
                              <Input placeholder="enter value..." {...field} />
                              <span className="self-center">m</span>
                            </div>
                          </FormControl>
                          <FormMessage />
                        </FormItem>
                      )}
                    />
                  </div>
                  <div className="grid grid-cols-3 gap-4">
                    <FormField
                      control={form.control}
                      name="loadCondition"
                      render={({ field }) => (
                        <FormItem className="w-full">
                          <FormLabel>Load Condition</FormLabel>
                          <Select
                            onValueChange={field.onChange}
                            defaultValue={field.value}
                          >
                            <FormControl className="w-full">
                              <SelectTrigger>
                                <SelectValue placeholder="AW Condition" />
                              </SelectTrigger>
                            </FormControl>
                            <SelectContent>
                              <SelectItem value="AW0">AW0</SelectItem>
                              <SelectItem value="AW1">AW1</SelectItem>
                              <SelectItem value="AW2">AW2</SelectItem>
                              <SelectItem value="AW3">AW3</SelectItem>
                              <SelectItem value="AW4">AW4</SelectItem>
                            </SelectContent>
                          </Select>
                          <FormMessage />
                        </FormItem>
                      )}
                    />
                  </div>
                </div>

                <Button
                  type="submit"
                  className="w-full"
                  disabled={isSubmitting}
                >
                  {isSubmitting ? "Mengirim..." : "Save Datas"}
                </Button>
              </form>
            </Form>
          </CardContent>
        </Card>
      </div>
    </SidebarProvider>
  );
}
